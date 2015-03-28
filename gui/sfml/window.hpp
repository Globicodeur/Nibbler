#pragma once

#include <SFML/Graphics.hpp>

namespace gui { struct GameInfo; }

class Window: public sf::RenderWindow {

public:

    Window(unsigned width, unsigned height);

    void render(const gui::GameInfo & info);

private:

    float boxWidth_, boxHeight_;

    sf::Image snakeImg_, foodImg_;
    sf::Texture snakeTx_, foodTx_;
    sf::Sprite snakeSp_, foodSp_;

};
