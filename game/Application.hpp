#pragma once

#include <memory>

#include "gui/spec.hpp"

class GameEngine;
class GuiManager;

class Application {

public:
                                Application(int argc, char **argv);
                                ~Application(void);

                                void run();

private:
    std::unique_ptr<GameEngine> engine_;
    std::unique_ptr<GuiManager> gui_;

    void                        handleInput(gui::InputType input);

                                Application(void);
                                Application(const Application &);
    Application &               operator=(const Application &);

};
