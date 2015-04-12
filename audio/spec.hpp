#pragma once

namespace audio {

    enum class Sound {
        FoodEaten,
        Dead,
    };

    struct Player {

        struct SharedObjectInfo {
            using Getter = Player * (*)(void);
            static constexpr const char * getterName() { return "get"; }
        };

        virtual         ~Player(void)       = default;
        virtual void    play(Sound sound)   = 0;

    };

}
