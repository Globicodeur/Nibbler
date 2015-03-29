#pragma once

#include "Snake.hpp"

class GameEngine {

public:
    bool            running;
    int             width;
    int             height;
    Snake           snake;
    Position        food;

                    GameEngine(unsigned width, unsigned height);
                    ~GameEngine(void) = default;

    void            update(void);

private:

                    GameEngine(void);
                    GameEngine(const GameEngine &copy);
    GameEngine &    operator=(const GameEngine &copy);

    void            spawnFood(void);
};
