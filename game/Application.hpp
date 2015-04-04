#pragma once

#include <memory>

#include "gui/spec.hpp"

#include "tools/SharedObjectCollection.hpp"

class GameEngine;

class Application {

public:
                                Application(int argc, char **argv);
                                ~Application(void);

    // 42 norme
                                Application(void)                   = delete;
                                Application(const Application &)    = delete;
    Application &               operator=(const Application &)      = delete;
    //

                                void run();

private:
    using GuiManager            = SharedObjectCollection<gui::Canvas>;

    std::unique_ptr<GameEngine> engine_;
    GuiManager                  gui_;

    void                        handleInput(gui::InputType input);
    void                        render(void);
};
