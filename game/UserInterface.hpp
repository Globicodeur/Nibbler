#pragma once

#include "tools/SharedObjectCollection.hpp"

#include "gui/spec.hpp"
#include "audio/spec.hpp"

class UserInterface {

    using GraphicsManager   = SharedObjectCollection<gui::Canvas>;
    using AudioManager      = SharedObjectCollection<audio::Player>;

public:
                            UserInterface(void);

    gui::Inputs             getInputs(void);

private:
    GraphicsManager         graphics_;
    AudioManager            audio_;
};
