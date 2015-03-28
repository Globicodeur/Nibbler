// #include <memory>

#include "Canvas.hpp"

// static std::unique_ptr<Window> window;

extern "C" {

    // void init(unsigned width, unsigned height) {
    //     window.reset(new Window { width, height });
    // }

    // void clean() {
    //     window.reset();
    // }

    // void draw(const gui::GameInfo & info) {
    //     window->clear();
    //     window->render(info);
    //     window->display();
    // }

    // gui::InputType getInput() {
    //     return window->getInput();
    // }

    gui::Canvas * get(unsigned width, unsigned height) {
        return new SDLCanvas { width, height };
    }

}
