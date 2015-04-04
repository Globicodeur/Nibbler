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
                        ~GameEngine(void) = default;

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
    void                spawnPlayer(unsigned id);

                        GameEngine(const GameEngine &copy);
    GameEngine &        operator=(const GameEngine &copy);
};
