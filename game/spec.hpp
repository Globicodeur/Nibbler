#pragma once

#include <signals/literal/from.hpp>

namespace spec {

    enum class Event {
        UpP1,
        DownP1,
        LeftP1,
        RightP1,
        UpP2,
        DownP2,
        LeftP2,
        RightP2,
        Exit,
        ChangeGui1,
        ChangeGui2,
        ChangeGui3,
        PlaySound,
    };

    using EventDispatcher = signals::literal::from<Event>;

}
