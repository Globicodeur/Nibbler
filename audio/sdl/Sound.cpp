#include "Sound.hpp"

#include <iostream>

static void         audioCallback(void *userData, Uint8 *stream, int len) {
    auto sound = static_cast<SDLSound*>(userData);

    if (sound->playLen == 0)
    {
        SDL_PauseAudioDevice(sound->dev, 1);
        return ;
    }

    len = std::min(static_cast<Uint32>(len), sound->playLen);
    memcpy(stream, sound->playPos, len);
    SDL_MixAudioFormat(stream, sound->playPos, AUDIO_S16, len, SDL_MIX_MAXVOLUME);

    sound->playPos += len;
    sound->playLen -= len;
}

SDLSound::SDLSound(const std::string & sound):
    dev { 0 },
    buffer_ { nullptr } {
    if (!SDL_LoadWAV(sound.c_str(), &sound_, &buffer_, &bufferLen_))
        std::cerr << SDL_GetError() << std::endl;
    sound_.callback = &audioCallback;
    sound_.userdata = this;
}

SDLSound::~SDLSound(void) {
    if (buffer_)
        SDL_FreeWAV(buffer_);
    SDL_CloseAudioDevice(dev);
}

void                SDLSound::play(void) {
    SDL_CloseAudioDevice(dev);
    playPos = buffer_;
    playLen = bufferLen_;
    dev = SDL_OpenAudioDevice(nullptr, 0, &sound_, nullptr, 0);
    SDL_PauseAudioDevice(dev, 0);
}
