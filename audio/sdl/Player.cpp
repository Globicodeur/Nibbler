#include "Player.hpp"
#include "Sound.hpp"

SDLPlayer::SDLPlayer(void) {
    SDL_Init(SDL_INIT_AUDIO);
    sounds[audio::FoodEaten] = new SDLSound(EAT_PATH);
    sounds[audio::Dead] = new SDLSound(DIE_PATH);
}

SDLPlayer::~SDLPlayer(void) {
    for (const auto & i : sounds) {
        delete std::get<1>(i);
    }
    SDL_Quit();
}

void            SDLPlayer::play(audio::SoundType sound) {
    sounds[sound]->play();
}
