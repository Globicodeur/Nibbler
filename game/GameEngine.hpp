#pragma once

#include "Snake.hpp"

class GameEngine {

public:
    static int      width, height;

    bool            running;
    Snake           snake;
    Position        food;

                    GameEngine(void);
                    ~GameEngine(void) = default;

    void            update(void);

private:
    void            spawnFood(void);

                    GameEngine(const GameEngine &copy);
    GameEngine &    operator=(const GameEngine &copy);
};
