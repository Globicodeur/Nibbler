#pragma once

#include "../gui/gui_spec.hpp"

class GameEngine;
class DynamicLibrary;

class GuiManager {

public:
    using LibraryNames  = std::vector<std::string>;

    GuiManager(unsigned width, unsigned height);
    ~GuiManager();

    void draw(const GameEngine & game) const;
    gui::InputType getInput() const;

    void changeLibrary(LibraryNames::size_type i);
    bool isValid() const;

private:
    using Libraries = std::vector<std::unique_ptr<DynamicLibrary>>;

    GuiManager(const GuiManager &);
    GuiManager & operator=(const GuiManager &);

    unsigned width_, height_;

    static const LibraryNames LIBRARY_NAMES;
    Libraries libraries_;
    DynamicLibrary * currentLibrary_;
};
