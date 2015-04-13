#pragma once

#include "tools/SharedObjectCollection.hpp"

#include "gui/spec.hpp"
#include "audio/spec.hpp"

class GameEngine;

class UserInterface {

    using GraphicsManager   = SharedObjectCollection<gui::Canvas>;
    using AudioManager      = SharedObjectCollection<audio::Player>;

public:
                            UserInterface(void);
    // 42 norme
                            ~UserInterface(void)                    = default;
                            UserInterface(const UserInterface &)    = delete;
    UserInterface &         operator=(const UserInterface &)        = delete;
    //

    gui::Inputs             getInputs(void);
    void                    render(const GameEngine &);
    void                    render(const gui::GameInfo &);

private:
    GraphicsManager         graphics_;
    AudioManager            audio_;
};
