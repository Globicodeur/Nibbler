#include "GuiManager.hpp"
#include "GameEngine.hpp"
#include "DynamicLibrary.hpp"
#include "Snake.hpp"

#include <algorithm>

const GuiManager::LibraryNames GuiManager::LIBRARY_NAMES = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};

GuiManager::GuiManager(unsigned width, unsigned height):
    width_(width), height_(height),
    currentLibrary_(nullptr)
{
    for (auto name: LIBRARY_NAMES)
        libraries_.emplace_back(new DynamicLibrary { name });

    changeLibrary(rand() % libraries_.size());
}

GuiManager::~GuiManager() {
    (*currentLibrary_->clean)();
}

bool GuiManager::isValid() const
{
    return std::all_of(
        libraries_.begin(),
        libraries_.end(),
        [](const auto & lib) { return lib->isValid(); }
    );
}

void GuiManager::draw(const GameEngine & game) const {
    gui::GameInfo info;

    for (auto pos: game.snake->body())
        info.snake.emplace_back(pos.x, pos.y);
    info.food = { game.food.x, game.food.y };

    (*currentLibrary_->draw)(info);
}

gui::InputType GuiManager::getInput() const {
    return (*currentLibrary_->getInput)();
}

void GuiManager::changeLibrary(LibraryNames::size_type i) {
    if (i < LIBRARY_NAMES.size()) {
        auto newLibrary = libraries_.at(i).get();
        if (newLibrary != currentLibrary_) {
            if (currentLibrary_)
                (*currentLibrary_->clean)();
            (*newLibrary->init)(width_, height_);
            currentLibrary_ = newLibrary;
        }
    }
}
