#include "window.hpp"

#include "../gui_spec.hpp"

Window::Window(uint width, uint height):
    sf::RenderWindow {
        sf::VideoMode { gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT },
        gui::WINDOW_TITLE_PREFIX + "SFML"
    },
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height },
    isClosed_ { false } {

}
bool Window::isClosed() const {
    return isClosed_;
}

void Window::processEvents() {
    while (pollEvent(event_)) {
        if (event_.type == sf::Event::Closed)
            isClosed_ = true;
    }
}

void Window::render(const gui::GameInfo & info) {
    (void)info;
}
