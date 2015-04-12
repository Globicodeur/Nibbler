#pragma once

#include <signals/literal/from.hpp>

namespace spec {

    enum class Event {
        ChangeDirection,
        Exit,
        ChangeGui1,
        ChangeGui2,
        ChangeGui3,
        PlaySound,
    };

    using EventDispatcher = signals::literal::from<Event>;

}
