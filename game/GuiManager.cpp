#include "GuiManager.hpp"
#include "GameEngine.hpp"

// #include <algorithm>

const GuiManager::LibraryNames GuiManager::LIBRARY_NAMES = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};

GuiManager::GuiManager(unsigned width, unsigned height):
    currentLibrary_(nullptr)
{
    for (auto name: LIBRARY_NAMES)
        libraries_.emplace_back(new GraphicLibrary { name, width, height });

    changeLibrary(rand() % libraries_.size());
}

GuiManager::~GuiManager() {
    // (*currentLibrary_->clean)();
}

bool GuiManager::isValid() const
{
    // return std::all_of(
    //     libraries_.begin(),
    //     libraries_.end(),
    //     [](const auto & lib) { return lib->isValid(); }
    // );
    return true;
}

void GuiManager::draw(const GameEngine & game) const {
    gui::GameInfo info;

    for (auto pos: game.snake.body())
        info.snake.emplace_back(pos.x, pos.y);
    info.food = { game.food.x, game.food.y };

    currentLibrary_->get()->draw(info);
}

gui::Inputs GuiManager::getInputs() const {
    return currentLibrary_->get()->getInputs();
}

void GuiManager::changeLibrary(LibraryNames::size_type i) {
    if (i < LIBRARY_NAMES.size()) {
        auto newLibrary = libraries_.at(i).get();
        if (newLibrary != currentLibrary_) {
            if (currentLibrary_)
                currentLibrary_->get()->setVisible(false);
            newLibrary->get()->setVisible(true);
            currentLibrary_ = newLibrary;
        }
    }
}
