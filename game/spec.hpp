#pragma once

#include <signals/literal/from.hpp>

namespace spec {

    enum class Event {
        ChangeDirection,
        Exit,
        ChangeGui,
        PlaySound,
    };

    using EventDispatcher = signals::literal::from<Event>;

}
