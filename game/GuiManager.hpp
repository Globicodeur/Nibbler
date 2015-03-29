#pragma once

#include "gui/spec.hpp"
#include "tools/SharedObject.hpp"

class GameEngine;

class GuiManager {

public:
                            GuiManager(void);
                            ~GuiManager(void) = default;

    void                    draw(const GameEngine & game) const;
    gui::Inputs             getInputs(void) const;

    void                    changeLibrary(size_t i);

private:
    using GraphicLibrary    = SharedObject<gui::Canvas>;
    using Libraries         = std::vector<std::unique_ptr<GraphicLibrary>>;

    Libraries               libraries_;
    GraphicLibrary          *currentLibrary_;

                            GuiManager(const GuiManager &);
                            GuiManager & operator=(const GuiManager &);
};
