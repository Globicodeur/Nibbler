#pragma once

#include "gui/spec.hpp"
#include "SharedObject.hpp"

class GameEngine;

class GuiManager {

public:
    using LibraryNames  = std::vector<std::string>;

    GuiManager(unsigned width, unsigned height);
    ~GuiManager();

    void draw(const GameEngine & game) const;
    gui::Inputs getInputs() const;

    void changeLibrary(LibraryNames::size_type i);
    bool isValid() const;

private:
    using GraphicLibrary = SharedObject<
        gui::Canvas,
        gui::CanvasGetter,
        gui::CANVAS_GETTER_FUNC_NAME
    >;
    using Libraries = std::vector<std::unique_ptr<GraphicLibrary>>;

    GuiManager(const GuiManager &);
    GuiManager & operator=(const GuiManager &);

    static const LibraryNames LIBRARY_NAMES;
    Libraries libraries_;
    GraphicLibrary * currentLibrary_;
};
