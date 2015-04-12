#include "Player.hpp"

#include "Sound.hpp"

#include <unordered_map>

static const char EAT_PATH[] = "./audio/sfml/assets/pacman_eatfruit.wav";
static const char DIE_PATH[] = "./audio/sfml/assets/pacman_death.wav";

using SoundMap = std::unordered_map<audio::Sound, std::shared_ptr<SFMLSound>>;
static const SoundMap SOUNDS = {
    { audio::Sound::FoodEaten, std::make_shared<SFMLSound>(EAT_PATH) },
    { audio::Sound::Dead,      std::make_shared<SFMLSound>(DIE_PATH) },
};

void SFMLPlayer::play(audio::Sound sound) {
    auto soundIt = SOUNDS.find(sound);
    if (soundIt != SOUNDS.end()) {
        soundIt->second->play();
    }
}
