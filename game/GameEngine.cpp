#include "GameEngine.hpp"
#include "GameOptions.hpp"
#include "Snake.hpp"

#include "tools/math.hpp"

#include "python/Wrapper.hpp"

#include "spec.hpp"
#include "audio/spec.hpp"
#include "gui/spec.hpp"

#include <algorithm>
#include <cstdlib>

static const auto DEFAULT_STEP_INTERVAL = 100u;

using spec::Event;
using Dispatcher = spec::EventDispatcher;

GameEngine::GameEngine(void):
    running_        { true },
    stepInterval_   { DEFAULT_STEP_INTERVAL } {

    Dispatcher::on_<Event::ChangeDirection>([this](size_t i, Direction dir) {
        turnSnake(i, dir);
    });
    Dispatcher::on<Event::Exit>([this] {
        running_ = false;
    });
    Dispatcher::on_<Event::NetworkPlayerLeft>([this](size_t i) {
        snakes_[i].installAi();
    });

    for (unsigned i = 0; i < GameOptions::snakeCount; ++i)
        spawnPlayer(i, i < GameOptions::playerCount);
    if (GameOptions::obstacles)
        spawnObstacles();
    spawnFood();
}

void GameEngine::update(void) {
    if (timer_.elapsed() >= stepInterval_) {
        timer_.reset();

        for (auto & snake: snakes_) {
            if (snake.isAlive())
                updateSnake(snake);
        }

        resolveSnakeCollisions();

        bool anyAlive = std::any_of(
            snakes_.begin(),
            snakes_.end(),
            std::mem_fn(&Snake::isAlive)
        );
        if (!anyAlive)
            running_ = false;

        notifyDraw();
    }
}

bool GameEngine::isRunning(void) const {
    return running_;
}

void GameEngine::turnSnake(size_t i, Direction dir) {
    if (i < snakes_.size()) {
        auto & snake = snakes_.at(i);
        if (snake.isPlayer())
            snake.turn(dir);
    }
}

void GameEngine::updateSnake(Snake & snake) {
    if (!snake.isPlayer())
        execAi(snake);

    snake.move();

    auto & head = snake.head();
    // Check arena bounds
    if (head.x < 0 || head.x >= GameOptions::width ||
        head.y < 0 || head.y >= GameOptions::height) {
        if (!GameOptions::torus)
            killSnake(snake);
        else {
            snake.setHeadPosition({
                negativeMod(head.x, GameOptions::width),
                negativeMod(head.y, GameOptions::height),
            });
        }
    }

    // Check food collision
    if (head == food_) {
        snake.eat();
        stepInterval_ *= 0.98;
        stepInterval_ = std::max(stepInterval_, 10u);
        Dispatcher::emit<Event::PlaySound>(audio::Sound::FoodEaten);
        spawnFood();
    }

    // Check obstacle collision
    if (inObstacle(head))
        killSnake(snake);

    // Check snake collision with itself
    auto bodyIt = std::find(
        std::next(snake.body().begin()),
        snake.body().end(),
        head
    );
    if (bodyIt != snake.body().end())
        killSnake(snake);
}

void GameEngine::killSnake(Snake & snake) {
    snake.die();
    Dispatcher::emit<Event::PlaySound>(audio::Sound::Dead);
}

void GameEngine::execAi(Snake & snake) {
    auto aliveAis = std::count_if(
        snakes_.begin(),
        snakes_.end(),
        [](const Snake & s) { return !s.isPlayer() && s.isAlive(); }
    );
    // We should never be dividing by zero because being in this function
    // guarantees at least one Ai to be alive
    auto timeout = stepInterval_ / aliveAis;

    std::vector<Snake::Body> bodies;
    std::transform(
        snakes_.begin(),
        snakes_.end(),
        std::back_inserter(bodies),
        std::mem_fn(&Snake::body)
    );

    Python::exec(
        [this, &snake, &bodies](const auto & globals) {
            auto ai = globals["ai"];
            ai(boost::ref(snake), bodies, food_, obstacles_);
        },
        std::max(timeout / 2, 1l) // Being extra careful here
    );
}

void GameEngine::resolveSnakeCollisions(void) {
    std::vector<unsigned> dead;

    for (unsigned i = 0; i < snakes_.size(); ++i) {
        for (unsigned j = 0; j < snakes_.size(); ++j) {
            if (i == j)
                continue ;

            auto & snake = snakes_.at(i);
            auto & other = snakes_.at(j);

            if (!snake.isAlive() || !other.isAlive())
                continue ;

            auto bodyIt = std::find(
                other.body().begin(),
                other.body().end(),
                snake.head()
            );
            if (bodyIt != other.body().end())
                dead.push_back(i);
        }
    }

    for (auto i: dead)
        killSnake(snakes_.at(i));
}

bool GameEngine::inSnakes(const Position & position) const {
    auto inSnake = [&](const auto & snake) {
        auto bodyIt = std::find(
            snake.body().begin(),
            snake.body().end(),
            position
        );
        return bodyIt != snake.body().end();
    };

    return std::any_of(snakes_.begin(), snakes_.end(), inSnake);
}

bool GameEngine::inObstacle(const Position & position) const {
    auto obstacleIt = std::find(
        obstacles_.begin(),
        obstacles_.end(),
        position
    );
    return obstacleIt != obstacles_.end();
}

void GameEngine::spawnFood(void) {
    do {
        food_ = {
            rand() % GameOptions::width,
            rand() % GameOptions::height
        };
    } while (inSnakes(food_) || inObstacle(food_));
}

void GameEngine::spawnPlayer(unsigned id, bool isPlayer) {
    static const auto SNAKE_INITIAL_SIZE = 4u;

    Snake::Body body;

    for (unsigned i = 0; i < SNAKE_INITIAL_SIZE; ++i)
        body.emplace_back(
            id * (GameOptions::width / 2 / GameOptions::snakeCount) +
                GameOptions::width / 4,
            GameOptions::height / 2 - 1 + i * (id % 2 ? 1 : -1)
        );

    snakes_.emplace_back(body, isPlayer, id % 2 ? Up : Down, id);
}

void GameEngine::spawnObstacles(void) {
    static const auto OBSTACLE_RATIO = 0.03;
    static const auto tooCloseToSnakes = [this](const Position & pos) {
        auto tooClose = [&pos](const Position & other) {
            auto dist = std::hypot(pos.x - other.x, pos.y - other.y);
            return dist < 5.;
        };
        auto tooCloseToSnake = [&tooClose](const Snake & snake) {
            return std::any_of(
                snake.body().begin(),
                snake.body().end(),
                tooClose
            );
        };
        return std::any_of(snakes_.begin(), snakes_.end(), tooCloseToSnake);
    };

    Position obstacle;
    unsigned obstacleCount = GameOptions::width * GameOptions::height * OBSTACLE_RATIO;

    while (obstacleCount--) {
        auto maxRetries = 20; // Avoid infinite loops on small maps
        do {
            obstacle = {
                rand() % GameOptions::width,
                rand() % GameOptions::height
            };
            if (!--maxRetries)
                break ;
        } while (tooCloseToSnakes(obstacle) || inObstacle(obstacle));

        if (maxRetries)
            obstacles_.push_back(obstacle);
    }
}

void GameEngine::notifyDraw() const {
    gui::GameState::Snakes snakes;

    for (const auto & snake: snakes_) {
        if (snake.isAlive())
            snakes.push_back({ snake.id(), snake.body() });
    }

    Dispatcher::emit<Event::Draw, gui::GameState>({
        snakes,
        food_,
        obstacles_
    });
}
