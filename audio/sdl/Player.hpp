#pragma once

#include "spec.hpp"

class SDLPlayer: public audio::Player {

public:
                    SDLPlayer(void);

    // 42 norme
    virtual         ~SDLPlayer(void)                = default;
                    SDLPlayer(const SDLPlayer &)    = delete;
    SDLPlayer &     operator=(const SDLPlayer &)    = delete;
    //

    virtual void    play(audio::SoundType sound);

};
