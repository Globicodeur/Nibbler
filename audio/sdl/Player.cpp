#include "Player.hpp"

Uint8           *eatBuffer;
Uint32          eatBufferLen;
Uint8           *dieBuffer;
Uint32          dieBufferLen;
Uint8           *playPos;
Uint32          playLen;

static void        audioCallback(void *userData, Uint8 *stream, int len) {
    (void)userData;

    if (playLen == 0)
        return ;

    len = ((Uint32)len > playLen ? playLen : len);
    memcpy(stream, playPos, len);
    SDL_MixAudio(stream, playPos, len, SDL_MIX_MAXVOLUME);

    playPos += len;
    playLen -= len;
}

SDLPlayer::SDLPlayer(void) {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_LoadWAV("./audio/sdl/assets/nyan.wav", &eatSound_, &eatBuffer, &eatBufferLen);
    SDL_LoadWAV("./audio/sdl/assets/cry.wav", &dieSound_, &dieBuffer, &dieBufferLen);
    eatSound_.callback = &audioCallback;
    eatSound_.userdata = 0;
    dieSound_.callback = &audioCallback;
    dieSound_.userdata = 0;
}

void            SDLPlayer::play(audio::SoundType sound) {
    if (sound == audio::FoodEaten)
    {
        playPos = eatBuffer;
        playLen = eatBufferLen;
        SDL_OpenAudio(&eatSound_, nullptr);
        SDL_PauseAudio(0);
    }
    else if (sound == audio::Dead)
    {
        playPos = dieBuffer;
        playLen = dieBufferLen;
        SDL_OpenAudio(&dieSound_, nullptr);
        SDL_PauseAudio(0);
    }
    // while (playLen > 0)
        // SDL_Delay(100);
    // SDL_CloseAudio();
    // SDL_FreeWAV(soundBuffer);
}
