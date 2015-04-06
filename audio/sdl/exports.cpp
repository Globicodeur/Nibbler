#include <type_traits>

#include "Player.hpp"

extern "C" {

    audio::Player * get(void) {
        return new SDLPlayer;
    }

}

static_assert(
    std::is_same<
        decltype(&get),
        audio::Player::SharedObjectInfo::Getter
    >::value,
    "Invalid exported function"
);

