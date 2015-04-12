#pragma once

#include "spec.hpp"

class SFMLPlayer: public audio::Player {

public:

    // 42 norme
                    SFMLPlayer(void)                = default;
    virtual         ~SFMLPlayer(void)               = default;
                    SFMLPlayer(const SFMLPlayer &)  = delete;
    SFMLPlayer &    operator=(const SFMLPlayer &)   = delete;
    //

    virtual void    play(audio::Sound sound);
};
