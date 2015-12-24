#pragma once

#include <functional>

#include "Snake.hpp"

#include "tools/Timer.hpp"

class GameEngine {

    using Snakes        = std::vector<Snake>;

public:
                        GameEngine(void);

    void                update(void);

    bool                isRunning(void) const;

private:
    using StepTimer     = Timer<std::chrono::milliseconds>;
    using Obstacles     = std::vector<Position>;

    bool                running_;
    StepTimer           timer_;
    unsigned            stepInterval_;

    Snakes              snakes_;
    Position            food_;
    Obstacles           obstacles_;

    void                turnSnake(size_t i, Direction dir);
    void                updateSnake(Snake & snake);
    void                killSnake(Snake & snake);
    void                execAi(Snake & snake);
    void                resolveSnakeCollisions(void);

    bool                inSnakes(const Position &) const;
    bool                inObstacle(const Position &) const;

    void                spawnFood(void);
    void                spawnPlayer(unsigned id, bool isPlayer);
    void                spawnObstacles(void);

    void                notifyDraw(void) const;
};
