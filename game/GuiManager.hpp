#pragma once

#include "nibbler.hpp"
#include "../gui/gui_spec.hpp"

class GameEngine;

class GuiManager {

    using init_t        = void (*)(uint, uint);
    using clean_t       = void (*)();
    using draw_t        = void (*)(const gui::GameInfo &);
    using getInput_t    = gui::InputType (*)();

public:

    using LibraryNames  = std::vector<std::string>;

    GuiManager(uint width, uint height, const LibraryNames & libraries);
    ~GuiManager();

    void draw(const GameEngine & game) const;
    gui::InputType getInput() const;

    bool changeLibrary(LibraryNames::size_type i);

private:
    init_t                  init_;
    clean_t                 clean_;
    draw_t                  draw_;
    getInput_t              getInput_;

    uint                    width_, height_;

    const LibraryNames      libraries_;
    void                    *handle_;
    LibraryNames::size_type currentIndex_;

    template<class T>
    bool        dlsymSafe(T & symbol, const char *toGet) {
        char    *error;

        symbol = reinterpret_cast<T>(dlsym(handle_, toGet));
        if ((error = dlerror()) != nullptr)  {
            std::cerr << error << std::endl;
            return false;
        }
        return true;
    }

                        GuiManager(const GuiManager &) = default;
    GuiManager &        operator=(const GuiManager &) = default;
};
