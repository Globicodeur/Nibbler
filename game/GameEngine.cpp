#include "GameEngine.hpp"
#include "Snake.hpp"

#include <algorithm>
#include <cstdlib>

int GameEngine::width { };
int GameEngine::height { };
bool GameEngine::torus = false;
unsigned GameEngine::players = 1;

static const char * AUDIO_LIBRARY_NAMES[] = {
    // "./nibbler_audio_sdl.so",
    // "./nibbler_audio_sfml.so",
    "./nibbler_audio_qt.so",
};

GameEngine::GameEngine(void):
    running { true } {
    // Randomness
    srand(time(nullptr));

    for (unsigned i = 0; i < players; ++i)
        spawnPlayer(i);
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
    if (i < snakes.size())
        snakes.at(i).turn(dir);
}

void GameEngine::updateSnake(Snake & snake) {
    // Move Snake
    snake.move();

    // Check arena bounds
    if (snake.head().x < 0 || snake.head().x >= width ||
        snake.head().y < 0 || snake.head().y >= height) {
        if (!torus) {
            audio_->play(audio::Dead);
            snake.die();
        }
        else {
            auto head = snake.head();
            snake.setHeadPosition({
                head.x < 0 ? head.x + width : head.x % width,
                head.y < 0 ? head.y + height : head.y % height
            });
        }
    }

    // Check food collision
    if (snake.head() == food) {
        snake.eat();
        audio_->play(audio::FoodEaten);
        spawnFood();
    }

    // Check snake collision
    auto bodyIt = std::find(
        std::next(snake.body().begin()),
        snake.body().end(),
        snake.head()
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
        food = { rand() % width, rand() % height };
        inABody = std::any_of(
            snakes.begin(),
            snakes.end(),
            foodInSnake
        );
    } while (inABody);
}

void GameEngine::spawnPlayer(unsigned id) {
    static const auto SNAKE_INITIAL_SIZE = 4u;
    static_assert(SNAKE_INITIAL_SIZE > 0, "Snake size cannot be zero");

    Snake::Body body;

    for (unsigned i = 0; i < SNAKE_INITIAL_SIZE; ++i)
        body.emplace_back(id * (width / players), height / 2 - 1 + i);

    snakes.emplace_back(body);
}
