#include "GuiManager.hpp"
#include "GameEngine.hpp"
#include "Snake.hpp"

#include <algorithm>

GuiManager::GuiManager(uint width, uint height, const LibraryNames & libraries):
    width_(width), height_(height),
    libraries_(libraries),
    handle_(nullptr) {

}

GuiManager::~GuiManager() {
    if (handle_) {
        (*clean_)();
        dlclose(handle_);
    }
}

void GuiManager::draw(const GameEngine & game) const {
    gui::GameInfo info;

    std::transform(
        game.snake->body().begin(),
        game.snake->body().end(),
        std::back_inserter(info.snake),
        [](const Position & pos) -> gui::GameInfo::position {
            return { pos.x, pos.y };
        }
    );
    info.food = { game.food.x, game.food.y };

    (*draw_)(info);
}

gui::InputType GuiManager::getInput() const {
    return (*getInput_)();
}

bool GuiManager::changeLibrary(LibraryNames::size_type i) {
    if (handle_) {
        if (i == currentIndex_)
            return true;
        (*clean_)();
        std::cout << dlclose(handle_) << std::endl;
        handle_ = nullptr;
    }

    handle_ = dlopen(libraries_[i].c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!handle_) {
        std::cerr << dlerror() << std::endl;
        return false;
    }

    bool allSymLoaded = true;
    allSymLoaded &= dlsymSafe(init_, "init");
    allSymLoaded &= dlsymSafe(clean_, "clean");
    allSymLoaded &= dlsymSafe(draw_, "draw");
    allSymLoaded &= dlsymSafe(getInput_, "getInput");
    if (!allSymLoaded)
        return false;

    (*init_)(width_, height_);
    currentIndex_ = i;
    return true;
}
