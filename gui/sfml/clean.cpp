#include <SFML/Graphics.hpp>

extern sf::RenderWindow window;

extern "C" void clean() {
    window.close();
}
