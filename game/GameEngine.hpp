#pragma once

#include "Snake.hpp"

class GameEngine {

public:
    bool                    running;
    int                     width;
    int                     height;
    Position                food;
    Snake           snake;

                    GameEngine(unsigned width, unsigned height);
                    ~GameEngine(void);
    void            spawnFood(void);
    void            update(void);

private:

                    GameEngine(void) = default;
                    GameEngine(const GameEngine &copy) = default;
    GameEngine &    operator=(const GameEngine &copy) = default;
};
