#pragma once

#include <QMediaPlayer>
#include <QGuiApplication>

#include "spec.hpp"

class QtPlayer: public audio::Player {

public:
                    QtPlayer(void);
    virtual         ~QtPlayer(void) = default;

    virtual void    play(audio::SoundType sound);

    QGuiApplication app;
    QMediaPlayer player;
};
