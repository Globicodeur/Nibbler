#include "GameEngine.hpp"
#include "Snake.hpp"

#include <algorithm>
#include <cstdlib>

int GameEngine::width = 32;
int GameEngine::height = 18;

GameEngine::GameEngine(void):
    running { true },
    snake { width, height } {
    // Randomness
    srand(time(nullptr));
    spawnFood();
}

void GameEngine::update(void) {
    if (timer_.elapsed() >= 100) {
        updateImpl();
        timer_.reset();
    }
}

void GameEngine::updateImpl(void) {
    // Move Snake
    snake.move();

    // Check arena bounds
    if (snake.head().x < 0 || snake.head().x >= width ||
        snake.head().y < 0 || snake.head().y >= height)
        running = false;

    // Check food collision
    if (snake.head() == food) {
        snake.eat();
        spawnFood();
    }

    // Check snake collision
    auto bodyIt = std::find(
        std::next(snake.body().begin()),
        snake.body().end(),
        snake.head()
    );
    if (bodyIt != snake.body().end())
        running = false;
}

void GameEngine::spawnFood(void) {
    Snake::Body::const_iterator bodyIt;

    do {
        food = { rand() % width, rand() % height };
        bodyIt = std::find(snake.body().begin(), snake.body().end(), food);
    } while (bodyIt != snake.body().end());
}
