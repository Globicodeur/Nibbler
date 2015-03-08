#include "GameEngine.hpp"
#include "Snake.hpp"

GameEngine::GameEngine(uint height, uint width): running(true), height(height), width(width) {
    snake = new Snake(height, width);
}

GameEngine::~GameEngine(void) {
    delete snake;
}

void        GameEngine::spawnFood(void) {
    bool    spawned = false;
    uint    y;
    uint    x;
    std::vector<position>   snakePos = snake->body;

    while (!spawned) {
        spawned = true;
        y = rand() % height;
        x = rand() % width;
        for (std::vector<position>::iterator i = snakePos.begin(); i != snakePos.end(); ++i) {
            if (y == std::get<0>(*i) && x == std::get<1>(*i))
                spawned = false;
        }
    }
    food = std::make_pair(y, x);
}
