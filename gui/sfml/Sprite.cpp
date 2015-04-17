#include "Sprite.hpp"

Sprite::Sprite(const sf::Color & color, float factorX, float factorY):
    sf::Sprite() {

    sf::Image img;
    img.create(1, 1, color);
    tx_.loadFromImage(img);
    setTexture(tx_);
    scale(factorX, factorY);
}
