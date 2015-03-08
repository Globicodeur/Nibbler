#pragma once

#include <SFML/Graphics.hpp>

namespace gui { struct GameInfo; }

class Window: public sf::RenderWindow {

public:

    Window(uint width, uint height);

    bool isClosed() const;

    void processEvents();

    void render(const gui::GameInfo & info);

private:

    float boxWidth_, boxHeight_;

    sf::Event event_;
    bool isClosed_;

    sf::Image snakeImg_, foodImg_;
    sf::Texture snakeTx_, foodTx_;
    sf::Sprite snakeSp_, foodSp_;

};
