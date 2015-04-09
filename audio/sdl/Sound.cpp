#include "Sound.hpp"

static void         audioCallback(void *userData, Uint8 *stream, int len) {
    auto sound = static_cast<SDLSound*>(userData);

    if (sound->playLen == 0)
    {
        SDL_PauseAudioDevice(sound->dev, 1);
        return ;
    }

    len = ((Uint32)len > sound->playLen ? sound->playLen : len);
    memcpy(stream, sound->playPos, len);
    SDL_MixAudioFormat(stream, sound->playPos, AUDIO_S16, len, SDL_MIX_MAXVOLUME);

    sound->playPos += len;
    sound->playLen -= len;
}

SDLSound::SDLSound(const std::string & sound) {
    SDL_LoadWAV(sound.c_str(), &sound_, &buffer, &bufferLen);
    sound_.callback = &audioCallback;
    sound_.userdata = this;
    dev = 0;
}

SDLSound::~SDLSound(void) {
    SDL_FreeWAV(buffer);
    SDL_CloseAudioDevice(dev);
}

void                SDLSound::play(void) {
    SDL_CloseAudioDevice(dev);
    playPos = buffer;
    playLen = bufferLen;
    dev = SDL_OpenAudioDevice(nullptr, 0, &sound_, nullptr, 0);
    SDL_PauseAudioDevice(dev, 0);
}

SDLSound &          SDLSound::operator=(const SDLSound & sound) {
    if (this != &sound)
    {
        buffer = sound.buffer;
        bufferLen = sound.bufferLen;
        playPos = sound.playPos;
        playLen = sound.playLen;
        dev = sound.dev;
        sound_ = sound.sound_;
    }
    return *this;
}
