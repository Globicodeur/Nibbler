#pragma once

#include "Snake.hpp"

#include "audio/spec.hpp"

#include "tools/SharedObjectCollection.hpp"
#include "tools/Timer.hpp"

class GameEngine {

public:
    bool                running;
    std::vector<Snake>  snakes;
    Position            food;

                        GameEngine(void);
    // 42 norme
                        ~GameEngine(void)                   = default;
                        GameEngine(const GameEngine &copy)  = delete;
    GameEngine &        operator=(const GameEngine &copy)   = delete;
    //

    void                update(void);
    void                turnSnake(size_t i, Direction dir);

private:
    using StepTimer     = Timer<std::chrono::milliseconds>;
    using AudioManager  = SharedObjectCollection<audio::Player>;

    StepTimer           timer_;
    AudioManager        audio_;

    void                updateSnake(Snake & snake);
    void                resolveSnakeCollisions(void);
    void                spawnFood(void);
    void                spawnPlayer(unsigned id, bool isPlayer);
};
