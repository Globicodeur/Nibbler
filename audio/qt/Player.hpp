#pragma once

#include <QMediaPlayer>
#include <QMediaContent>
#include <QFileInfo>

#include "spec.hpp"

class QtPlayer: public audio::Player {

public:
                    QtPlayer(void);

    // 42 norme
    virtual         ~QtPlayer(void)             = default;
                    QtPlayer(const QtPlayer &)  = delete;
    QtPlayer &      operator=(const QtPlayer &) = delete;
    //

    virtual void    play(audio::SoundType sound);

private:
    QMediaPlayer    player;
    QMediaContent   eatSound_;
};
