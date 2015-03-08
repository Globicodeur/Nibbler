#include <SFML/Graphics.hpp>

#include "../gui_spec.hpp"

extern sf::RenderWindow window;
bool has_quit;

extern "C" void draw(const gui::GameInfo & info) {
    // Check for window closed
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            has_quit = true;
            return ;
        }
    }

    window.clear();

    // Draw here
    (void)info;

    window.display();
}
