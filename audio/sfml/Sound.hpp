#pragma once

#include <SFML/Audio.hpp>
#include <string>

class SFMLSound {

public:
                    SFMLSound(const std::string &);

    void            play(void);

private:
    sf::SoundBuffer buff_;
    sf::Sound       sound_;
};
