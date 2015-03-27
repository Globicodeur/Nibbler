#pragma once

#include <memory>

#include "Position.hpp"

class Snake;

class GameEngine {

public:
    bool                    running;
    int                     width;
    int                     height;
    std::unique_ptr<Snake>  snake;
    Position                food;

                    GameEngine(unsigned width, unsigned height);
                    ~GameEngine(void);
    void            spawnFood(void);
    void            update(void);

private:

                    GameEngine(void) = default;
                    GameEngine(const GameEngine &copy) = default;
    GameEngine &    operator=(const GameEngine &copy) = default;
};
