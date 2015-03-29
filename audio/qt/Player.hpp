#pragma once

#include <QMediaPlayer>

#include "spec.hpp"

class QtPlayer: public audio::Player {

public:
                    QtPlayer(void) = default;
    virtual         ~QtPlayer(void) = default;

    virtual void    play(audio::SoundType sound);

private:
    QMediaPlayer    player;

                    QtPlayer(const QtPlayer &);
    QtPlayer &      operator=(const QtPlayer &);
};
