#include "GameEngine.hpp"
#include "GameOptions.hpp"
#include "Snake.hpp"

#include "tools/math.hpp"

#include <algorithm>
#include <cstdlib>

static const char * AUDIO_LIBRARY_NAMES[] = {
    // "./nibbler_audio_sdl.so",
    // "./nibbler_audio_sfml.so",
    "./nibbler_audio_qt.so",
};

GameEngine::GameEngine(void):
    running { true } {
    // Randomness
    srand(time(nullptr));

    for (unsigned i = 0; i < GameOptions::snakeCount; ++i)
        spawnPlayer(i, i < GameOptions::playerCount);
    spawnFood();

    audio_.load(AUDIO_LIBRARY_NAMES);
}

void GameEngine::update(void) {
    if (timer_.elapsed() >= 100) {
        for (auto & snake: snakes) {
            if (snake.isAlive())
                updateSnake(snake);
        }

        resolveSnakeCollisions();

        running = std::any_of(
            snakes.begin(),
            snakes.end(),
            std::mem_fn(&Snake::isAlive)
        );

        timer_.reset();
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
    snake.move();

    auto & head = snake.head();
    // Check arena bounds
    if (head.x < 0 || head.x >= GameOptions::width ||
        head.y < 0 || head.y >= GameOptions::height) {
        if (!GameOptions::torus) {
            audio_->play(audio::Dead);
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
        audio_->play(audio::FoodEaten);
        spawnFood();
    }

    // Check snake collision
    auto bodyIt = std::find(
        std::next(snake.body().begin()),
        snake.body().end(),
        head
    );
    if (bodyIt != snake.body().end()) {
        audio_->play(audio::Dead);
        snake.die();
    }
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
        snakes.at(i).die();
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
