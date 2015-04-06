#pragma once

#include <functional>

#include "Snake.hpp"

#include "audio/spec.hpp"
#include "tools/Timer.hpp"

class AudioManager;

class GameEngine {

    using PlayAudioF    = std::function<void (audio::SoundType)>;

public:
    bool                running;
    std::vector<Snake>  snakes;
    Position            food;

                        GameEngine(PlayAudioF playAudio);
    // 42 norme
                        GameEngine(void)                = delete;
                        ~GameEngine(void)               = default;
                        GameEngine(const GameEngine &)  = delete;
    GameEngine &        operator=(const GameEngine &)   = delete;
    //

    void                update(void);
    void                turnSnake(size_t i, Direction dir);

private:
    using StepTimer     = Timer<std::chrono::milliseconds>;

    StepTimer           timer_;
    unsigned            stepInterval_;

    PlayAudioF          playAudio_;

    void                updateSnake(Snake & snake);
    void                execAi(Snake & snake);
    void                resolveSnakeCollisions(void);
    void                spawnFood(void);
    void                spawnPlayer(unsigned id, bool isPlayer);
};
