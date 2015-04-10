#include "GameEngine.hpp"
#include "GameOptions.hpp"
#include "Snake.hpp"

#include "tools/math.hpp"

#include "python/Wrapper.hpp"

#include <algorithm>
#include <cstdlib>

static const auto DEFAULT_STEP_INTERVAL = 100u;

GameEngine::GameEngine(PlayAudioF playAudio):
    running         { true },
    stepInterval_   { DEFAULT_STEP_INTERVAL },
    playAudio_      { playAudio } {

    for (unsigned i = 0; i < GameOptions::snakeCount; ++i)
        spawnPlayer(i, i < GameOptions::playerCount);
    spawnFood();
}

void GameEngine::update(void) {
    if (timer_.elapsed() >= stepInterval_) {
        timer_.reset();

        for (auto & snake: snakes) {
            if (snake.isAlive())
                updateSnake(snake);
        }

        resolveSnakeCollisions();

        bool anyAlive = std::any_of(
            snakes.begin(),
            snakes.end(),
            std::mem_fn(&Snake::isAlive)
        );
        if (!anyAlive)
            running = false;
    }
}

void GameEngine::turnSnake(size_t i, Direction dir) {
    if (i < snakes.size()) {
        auto & snake = snakes.at(i);
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
        if (!GameOptions::torus) {
            playAudio_(audio::Dead);
            snake.die();
        }
        else {
            snake.setHeadPosition({
                negativeMod(head.x, GameOptions::width),
                negativeMod(head.y, GameOptions::height),
            });
        }
    }

    // Check food collision
    if (head == food) {
        snake.eat();
        stepInterval_ *= 0.98;
        stepInterval_ = std::max(stepInterval_, 10u);
        playAudio_(audio::FoodEaten);
        spawnFood();
    }

    // Check snake collision with itself
    auto bodyIt = std::find(
        std::next(snake.body().begin()),
        snake.body().end(),
        head
    );
    if (bodyIt != snake.body().end()) {
        playAudio_(audio::Dead);
        snake.die();
    }
}

void GameEngine::execAi(Snake & snake) {
    auto aiCount = GameOptions::snakeCount - GameOptions::playerCount;
    auto timeout = stepInterval_ / aiCount;

    std::vector<Snake::Body> bodies;
    std::transform(
        snakes.begin(),
        snakes.end(),
        std::back_inserter(bodies),
        std::mem_fn(&Snake::body)
    );

    Python::exec(
        [this, &snake, &bodies](const auto & globals) {
            auto ai = globals["ai"];
            ai(boost::ref(snake), bodies, food);
        },
        std::max(timeout / 2, 1u) // Being extra careful here
    );
}

void GameEngine::resolveSnakeCollisions(void) {
    std::vector<unsigned> dead;

    for (unsigned i = 0; i < snakes.size(); ++i) {
        for (unsigned j = 0; j < snakes.size(); ++j) {
            if (i == j)
                continue ;

            auto & snake = snakes.at(i);
            auto & other = snakes.at(j);

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
    {
        snakes.at(i).die();
        playAudio_(audio::Dead);
    }
}

void GameEngine::spawnFood(void) {
    static const auto foodInSnake = [this](const auto & snake) {
        auto bodyIt = std::find(
            snake.body().begin(),
            snake.body().end(),
            food
        );
        return bodyIt != snake.body().end();
    };

    bool inABody;
    do {
        food = { rand() % GameOptions::width, rand() % GameOptions::height };
        inABody = std::any_of(
            snakes.begin(),
            snakes.end(),
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

    snakes.emplace_back(body, isPlayer);
}
