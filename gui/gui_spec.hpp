#pragma once

#include <vector>
#include <utility>

namespace gui {

    using uint = unsigned int;

    enum class InputType {
        Up,
        Down,
        Left,
        Right,
        Exit,
        ChangeGui1,
        ChangeGui2,
        ChangeGui3,
    };

    struct GameInfo {

        using position = std::pair<uint, uint>;

        uint width, height;
        std::vector<position> snake;
        position food;

    };

}
