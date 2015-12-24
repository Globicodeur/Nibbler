#pragma once

#include <QMediaPlayer>

#include "spec.hpp"

class QtPlayer: public audio::Player {

public:
    virtual void    play(audio::Sound sound);

private:
    QMediaPlayer    player;
};
