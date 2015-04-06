#pragma once

#include <memory>

#include "tools/SharedObjectCollection.hpp"

#include "gui/spec.hpp"
#include "audio/spec.hpp"

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

                                void run(void);

private:
    using GuiManager            = SharedObjectCollection<gui::Canvas>;
    using AudioManager          = SharedObjectCollection<audio::Player>;

    GuiManager                  gui_;
    AudioManager                audio_;

    std::unique_ptr<GameEngine> engine_;

    void                        handleInput(gui::InputType input);
    void                        render(void);
};
