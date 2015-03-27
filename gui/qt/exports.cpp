#include <memory>
#include <QApplication>

#include "window.hpp"

static int FAKE_ARGC = 1;
static char * FAKE_ARGV[] = { 0 };

static std::unique_ptr<QApplication> app;
static std::unique_ptr<Window> window;

extern "C" {

    void init(unsigned width, unsigned height) {
        app.reset(new QApplication { FAKE_ARGC, FAKE_ARGV });
        app->setQuitOnLastWindowClosed(false);
        window.reset(new Window { width, height });
        window->show();
    }

    void clean() {
        window.reset();
        app.reset();
    }

    void draw(const gui::GameInfo & info) {
        window->draw(info);
    }

    gui::InputType getInput() {
        QApplication::processEvents();
        QApplication::sendPostedEvents();

        return window->lastInput();
    }

}
