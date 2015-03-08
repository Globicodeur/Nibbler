#include <SFML/Graphics.hpp>

sf::RenderWindow window;

extern "C" void init() {
    sf::VideoMode videoMode { 1920, 1080 };
    window.create(videoMode, "Nibbler SFML");
}
