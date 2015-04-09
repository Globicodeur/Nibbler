#pragma once

#include <SDL2/SDL.h>
#include <iostream>

#include "spec.hpp"

class SDLSound {

public:
    Uint8               *buffer;
    Uint32              bufferLen;
    Uint8               *playPos;
    Uint32              playLen;
    SDL_AudioDeviceID   dev;

                        SDLSound(void) = default;
                        SDLSound(const std::string &);
    virtual             ~SDLSound(void);
                        SDLSound(const SDLSound &) = delete;
    SDLSound &          operator=(const SDLSound &);

    void                play(void);

private:
    SDL_AudioSpec       sound_;

};
