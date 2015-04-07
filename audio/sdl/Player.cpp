#include "Player.hpp"

Uint8           *eatBuffer;
Uint32          eatBufferLen;
Uint8           *dieBuffer;
Uint32          dieBufferLen;
Uint8           *playPos;
Uint32          playLen;

static void        audioCallback(void *userData, Uint8 *stream, int len) {
    auto device = static_cast<SDL_AudioDeviceID*>(userData);

    if (playLen == 0)
    {
        SDL_PauseAudioDevice(*device, 1);
        return ;
    }

    len = ((Uint32)len > playLen ? playLen : len);
    memcpy(stream, playPos, len);
    SDL_MixAudioFormat(stream, playPos, AUDIO_S16, len, SDL_MIX_MAXVOLUME);

    playPos += len;
    playLen -= len;
}

SDLPlayer::SDLPlayer(void) {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_LoadWAV("./audio/sdl/assets/nyan.wav", &eatSound_, &eatBuffer, &eatBufferLen);
    SDL_LoadWAV("./audio/sdl/assets/cry.wav", &dieSound_, &dieBuffer, &dieBufferLen);
    eatSound_.callback = &audioCallback;
    eatSound_.userdata = &dev_;
    dieSound_.callback = &audioCallback;
    dieSound_.userdata = &dev_;
    dev_ = 0;
}

SDLPlayer::~SDLPlayer(void) {
    SDL_FreeWAV(eatBuffer);
    SDL_FreeWAV(dieBuffer);
}

void            SDLPlayer::play(audio::SoundType sound) {
    SDL_CloseAudioDevice(dev_);

    if (sound == audio::FoodEaten)
    {
        playPos = eatBuffer;
        playLen = eatBufferLen;
        dev_ = SDL_OpenAudioDevice(nullptr, 0, &eatSound_, nullptr, 0);
    }
    else if (sound == audio::Dead)
    {
        playPos = dieBuffer;
        playLen = dieBufferLen;
        dev_ = SDL_OpenAudioDevice(nullptr, 0, &dieSound_, nullptr, 0);
    }

    SDL_PauseAudioDevice(dev_, 0);
}
