#pragma once

#include <SFML/Graphics.hpp>

class Sprite: public sf::Sprite {

public:
                Sprite(const sf::Color &, float, float);

    // 42 norme
                Sprite(void)                = delete;
                ~Sprite(void)               = default;
                Sprite(const Sprite &)      = delete;
    Sprite &    operator=(const Sprite &)   = delete;
    //

private:
    sf::Texture tx_;
};
