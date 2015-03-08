#pragma once

#include "nibbler.hpp"

class Snake;

class GameEngine {

using position = std::pair<uint, uint>;

public:
    bool            running;
    int             height;
    int             width;
    Snake           *snake;
    position        food;

                    GameEngine(uint height, uint width);
                    ~GameEngine(void);
    void            spawnFood(void);

private:
                    GameEngine(void) = default;
                    GameEngine(const GameEngine &copy) = default;
    GameEngine &    operator=(const GameEngine &copy) = default;
};
