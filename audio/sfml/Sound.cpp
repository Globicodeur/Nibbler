#include "Sound.hpp"

SFMLSound::SFMLSound(const std::string & fileName) {
    buff_.loadFromFile(fileName);
    sound_.setBuffer(buff_);
}

void SFMLSound::play(void) {
    sound_.stop();
    sound_.setPlayingOffset(sf::Time::Zero);
    sound_.play();
}
