#pragma once

#include "Snake.hpp"

#include "tools/Timer.hpp"

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
    using StepTimer = Timer<std::chrono::milliseconds>;
    StepTimer       timer_;

    void            updateImpl(void);
    void            spawnFood(void);

                    GameEngine(const GameEngine &copy);
    GameEngine &    operator=(const GameEngine &copy);
};
