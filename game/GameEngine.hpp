#pragma once

#include "Snake.hpp"

#include "audio/spec.hpp"

#include "tools/SharedObjectCollection.hpp"
#include "tools/Timer.hpp"

class GameEngine {

public:
    static int          width, height;
    static bool         torus;

    bool                running;
    Snake               snake;
    Position            food;

                        GameEngine(void);
                        ~GameEngine(void) = default;

    void                update(void);

private:
    using StepTimer     = Timer<std::chrono::milliseconds>;
    using AudioManager  = SharedObjectCollection<audio::Player>;

    StepTimer           timer_;
    AudioManager        audio_;

    void                updateImpl(void);
    void                spawnFood(void);

                        GameEngine(const GameEngine &copy);
    GameEngine &        operator=(const GameEngine &copy);
};
