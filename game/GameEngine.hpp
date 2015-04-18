#pragma once

#include <functional>

#include "Snake.hpp"

#include "tools/Timer.hpp"

class GameEngine {

    using Snakes        = std::vector<Snake>;

public:
                        GameEngine(void);
    // 42 norme
                        ~GameEngine(void)               = default;
                        GameEngine(const GameEngine &)  = delete;
    GameEngine &        operator=(const GameEngine &)   = delete;
    //

    void                update(void);

    bool                isRunning(void) const;

private:
    using StepTimer     = Timer<std::chrono::milliseconds>;

    bool                running_;
    StepTimer           timer_;
    unsigned            stepInterval_;

    Snakes              snakes_;
    Position            food_;

    void                turnSnake(size_t i, Direction dir);
    void                updateSnake(Snake & snake);
    void                killSnake(Snake & snake);
    void                execAi(Snake & snake);
    void                resolveSnakeCollisions(void);
    void                spawnFood(void);
    void                spawnPlayer(unsigned id, bool isPlayer);
    void                notifyDraw(void);
};
