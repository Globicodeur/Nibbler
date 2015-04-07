#pragma once

#include <SDL2/SDL.h>

#include "spec.hpp"

class SDLPlayer: public audio::Player {

public:
                    SDLPlayer(void);
    virtual         ~SDLPlayer(void);;
                    SDLPlayer(const SDLPlayer &) = delete;
    SDLPlayer &     operator=(const SDLPlayer &) = delete;

    virtual void    play(audio::SoundType sound);

private:
    SDL_AudioSpec   eatSound_;
    SDL_AudioSpec   dieSound_;
    SDL_AudioDeviceID   dev_;

    // void            audioCallback(void *userData, Uint8 *stream, int len);
};
