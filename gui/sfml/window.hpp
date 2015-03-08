#pragma once

#include <SFML/Graphics.hpp>

namespace gui { struct GameInfo; }

class Window: public sf::RenderWindow {

public:

    Window();

    bool isClosed() const;

    void processEvents();

    void render(const gui::GameInfo & info);

private:

    sf::Event event_;
    bool isClosed_;

};
