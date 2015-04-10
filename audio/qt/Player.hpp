#pragma once

#include <QMediaPlayer>

#include "spec.hpp"

class QtPlayer: public audio::Player {

public:

    // 42 norme
                    QtPlayer(void)              = default;
    virtual         ~QtPlayer(void)             = default;
                    QtPlayer(const QtPlayer &)  = delete;
    QtPlayer &      operator=(const QtPlayer &) = delete;
    //

    virtual void    play(audio::SoundType sound);

private:
    QMediaPlayer    player;
};
