#pragma once

#include <SDL2/SDL.h>
#include <string>

class SDLSound {

public:
    Uint8               *playPos;
    Uint32              playLen;
    SDL_AudioDeviceID   dev;

                        SDLSound(const std::string &);
    virtual             ~SDLSound(void);

    // 42 norme
                        SDLSound(void)              = delete;
                        SDLSound(const SDLSound &)  = delete;
    SDLSound &          operator=(const SDLSound &) = delete;
    //

    void                play(void);

private:
    SDL_AudioSpec       sound_;

    Uint8               *buffer_;
    Uint32              bufferLen_;

};
