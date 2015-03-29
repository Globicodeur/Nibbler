#include "GuiManager.hpp"
#include "GameEngine.hpp"

#include <cstdlib>

static const char * LIBRARY_NAMES[] = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};

static constexpr auto LIBRARY_COUNT =
    sizeof(LIBRARY_NAMES) / sizeof(const char *);

constexpr char gui::Canvas::SharedObjectInfo::GETTER_NAME[];

GuiManager::GuiManager(void):
    currentLibrary_ { nullptr }
{
    for (auto name: LIBRARY_NAMES)
        libraries_.emplace_back(new GraphicLibrary {
            name,
            GameEngine::width,
            GameEngine::height
        });

    changeLibrary(rand() % LIBRARY_COUNT);
}

void GuiManager::draw(const GameEngine & game) const {
    currentLibrary_->get()->draw({
        game.snake.body(),
        game.food
    });
}

gui::Inputs GuiManager::getInputs() const {
    return currentLibrary_->get()->getInputs();
}

void GuiManager::changeLibrary(size_t i) {
    if (i < LIBRARY_COUNT) {
        auto newLibrary = libraries_.at(i).get();
        if (newLibrary != currentLibrary_) {
            if (currentLibrary_)
                currentLibrary_->release();
            newLibrary->get();
            currentLibrary_ = newLibrary;
        }
    }
}
