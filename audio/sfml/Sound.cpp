#include "Sound.hpp"

SFMLSound::SFMLSound(const std::string & fileName) {
    sound_.openFromFile(fileName);
}

void SFMLSound::play(void) {
    sound_.stop();
    sound_.setPlayingOffset(sf::Time::Zero);
    sound_.play();
}
