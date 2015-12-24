#pragma once

#include "spec.hpp"

class SFMLPlayer: public audio::Player {

public:
    virtual void    play(audio::Sound sound);
};
