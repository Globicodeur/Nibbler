#pragma once

#include "spec.hpp"

class SDLPlayer: public audio::Player {

public:
                    SDLPlayer(void);

    virtual void    play(audio::Sound sound);

};
