#pragma once

#include "gui/spec.hpp"
#include "SharedObject.hpp"

class GameEngine;

class GuiManager {

public:
    GuiManager(void);
    ~GuiManager(void) = default;

    void draw(const GameEngine & game) const;
    gui::Inputs getInputs(void) const;

    void changeLibrary(size_t i);

private:
    using GraphicLibrary = SharedObject<
        gui::Canvas,
        gui::CanvasGetter,
        gui::CANVAS_GETTER_FUNC_NAME
    >;
    using Libraries = std::vector<std::unique_ptr<GraphicLibrary>>;

    GuiManager(const GuiManager &);
    GuiManager & operator=(const GuiManager &);

    Libraries libraries_;
    GraphicLibrary * currentLibrary_;
};
