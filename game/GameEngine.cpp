#include "GameEngine.hpp"
#include "Snake.hpp"

#include <algorithm>
#include <cstdlib>

int GameEngine::width { };
int GameEngine::height { };
bool GameEngine::torus = false;

static const char * AUDIO_LIBRARY_NAMES[] = {
    // "./nibbler_audio_sdl.so",
    // "./nibbler_audio_sfml.so",
    "./nibbler_audio_qt.so",
};

GameEngine::GameEngine(void):
    running { true },
    snake { width, height } {
    // Randomness
    srand(time(nullptr));
    spawnFood();

    audio_.load(AUDIO_LIBRARY_NAMES);
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
        snake.head().y < 0 || snake.head().y >= height) {
        if (!torus) {
            audio_->play(audio::Dead);
            running = false;
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
        running = false;
    }
}

void GameEngine::spawnFood(void) {
    Snake::Body::const_iterator bodyIt;

    do {
        food = { rand() % width, rand() % height };
        bodyIt = std::find(snake.body().begin(), snake.body().end(), food);
    } while (bodyIt != snake.body().end());
}
