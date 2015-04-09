#pragma once

#include <SDL2/SDL.h>
#include <map>

#include "spec.hpp"

static const char EAT_PATH[] = "./audio/sdl/assets/nyan.wav";
static const char DIE_PATH[] = "./audio/sdl/assets/cry.wav";

class SDLSound;

class SDLPlayer: public audio::Player {

public:
                    SDLPlayer(void);
    virtual         ~SDLPlayer(void);
                    SDLPlayer(const SDLPlayer &) = delete;
    SDLPlayer &     operator=(const SDLPlayer &) = delete;

    virtual void    play(audio::SoundType sound);

private:
	std::map<audio::SoundType, SDLSound*>	sounds;

};
