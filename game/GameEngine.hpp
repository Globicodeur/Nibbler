#pragma once

#include <memory>

#include "Position.hpp"

class Snake;

class GameEngine {

public:
    bool                    running;
    int                     height;
    int                     width;
    std::unique_ptr<Snake>  snake;
    Position                food;

                    GameEngine(uint width, uint height);
                    ~GameEngine(void);
    void            spawnFood(void);
    void            update(void);

private:

                    GameEngine(void) = default;
                    GameEngine(const GameEngine &copy) = default;
    GameEngine &    operator=(const GameEngine &copy) = default;
};
