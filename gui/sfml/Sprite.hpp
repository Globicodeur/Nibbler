#pragma once

#include <SFML/Graphics.hpp>

class Sprite: public sf::Sprite {

public:
                Sprite(const sf::Color &, float, float);

private:
    sf::Texture tx_;
};
