#include "GameEngine.hpp"
#include "GameOptions.hpp"
#include "Snake.hpp"

#include "tools/math.hpp"

#include "python/Wrapper.hpp"

#include "spec.hpp"
#include "audio/spec.hpp"

#include <algorithm>
#include <cstdlib>

static const auto DEFAULT_STEP_INTERVAL = 100u;

using spec::Event;
using Dispatcher = spec::EventDispatcher;

GameEngine::GameEngine(void):
    running_        { true },
    stepInterval_   { DEFAULT_STEP_INTERVAL } {

    Dispatcher::on<Event::UpP1>    ([this] { turnSnake(0, Up);     });
    Dispatcher::on<Event::DownP1>  ([this] { turnSnake(0, Down);   });
    Dispatcher::on<Event::LeftP1>  ([this] { turnSnake(0, Left);   });
    Dispatcher::on<Event::RightP1> ([this] { turnSnake(0, Right);  });
    Dispatcher::on<Event::UpP2>    ([this] { turnSnake(1, Up);     });
    Dispatcher::on<Event::DownP2>  ([this] { turnSnake(1, Down);   });
    Dispatcher::on<Event::LeftP2>  ([this] { turnSnake(1, Left);   });
    Dispatcher::on<Event::RightP2> ([this] { turnSnake(1, Right);  });
    Dispatcher::on<Event::Exit>    ([this] { running_ = false;     });

    for (unsigned i = 0; i < GameOptions::snakeCount; ++i)
        spawnPlayer(i, i < GameOptions::playerCount);
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
    }
}

bool GameEngine::isRunning(void) const {
    return running_;
}

const GameEngine::Snakes & GameEngine::snakes(void) const {
    return snakes_;
}

const Position & GameEngine::food(void) const {
    return food_;
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
            ai(boost::ref(snake), bodies, food_);
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

void GameEngine::spawnFood(void) {
    static const auto foodInSnake = [this](const auto & snake) {
        auto bodyIt = std::find(
            snake.body().begin(),
            snake.body().end(),
            food_
        );
        return bodyIt != snake.body().end();
    };

    bool inABody;
    do {
        food_ = { rand() % GameOptions::width, rand() % GameOptions::height };
        inABody = std::any_of(
            snakes_.begin(),
            snakes_.end(),
            foodInSnake
        );
    } while (inABody);
}

void GameEngine::spawnPlayer(unsigned id, bool isPlayer) {
    static const auto SNAKE_INITIAL_SIZE = 4u;
    static_assert(SNAKE_INITIAL_SIZE > 0, "Snake size cannot be zero");

    Snake::Body body;

    for (unsigned i = 0; i < SNAKE_INITIAL_SIZE; ++i)
        body.emplace_back(
            id * (GameOptions::width / GameOptions::snakeCount),
            GameOptions::height / 2 - 1 + i
        );

    snakes_.emplace_back(body, isPlayer);
}
