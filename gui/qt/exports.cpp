#include "Canvas.hpp"

// static std::unique_ptr<QApplication> app;
// static std::unique_ptr<Window> window;

extern "C" {

    // void init(unsigned width, unsigned height) {
    //     app.reset(new QApplication { FAKE_ARGC, FAKE_ARGV });
    //     window.reset(new Window { width, height });
    //     window->show();
    // }

    // void clean() {
    //     window.reset();
    //     app.reset();
    // }

    // void draw(const gui::GameInfo & info) {
    //     window->draw(info);
    // }

    // gui::InputType getInput() {
    //     QApplication::processEvents();

    //     return window->lastInput();
    // }

    gui::Canvas * get(unsigned width, unsigned height) {
        return new QtCanvas { width, height };
    }

}
