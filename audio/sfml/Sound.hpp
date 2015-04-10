#pragma once

#include <SFML/Audio.hpp>
#include <string>

class SFMLSound {

public:
                    SFMLSound(const std::string &);

    // 42 norme
                    ~SFMLSound(void)                = default;
                    SFMLSound(const SFMLSound &)    = delete;
    SFMLSound &     operator=(const SFMLSound &)    = delete;
    //

    void            play(void);

private:
    sf::SoundBuffer buff_;
    sf::Sound       sound_;
};
