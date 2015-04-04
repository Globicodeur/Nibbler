#pragma once

#include <QMediaPlayer>
#include <QMediaContent>
#include <QFileInfo>

#include "spec.hpp"

class QtPlayer: public audio::Player {

public:
                    QtPlayer(void);
    virtual         ~QtPlayer(void) = default;

    virtual void    play(audio::SoundType sound);

private:
    QMediaPlayer    player;
    QMediaContent   eatSound_;

                    QtPlayer(const QtPlayer &);
    QtPlayer &      operator=(const QtPlayer &);
};
