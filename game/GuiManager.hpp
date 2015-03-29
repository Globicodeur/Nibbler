#pragma once

#include "gui/spec.hpp"
#include "SharedObject.hpp"

class GameEngine;

class GuiManager {

public:
    GuiManager(unsigned width, unsigned height);
    ~GuiManager() = default;

    void draw(const GameEngine & game) const;
    gui::Inputs getInputs() const;

    void changeLibrary(size_t i);
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

    Libraries libraries_;
    GraphicLibrary * currentLibrary_;
};
