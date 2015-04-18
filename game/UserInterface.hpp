#pragma once

#include "tools/SharedObjectCollection.hpp"

#include "gui/spec.hpp"
#include "audio/spec.hpp"

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

private:
    GraphicsManager         graphics_;
    AudioManager            audio_;
};
