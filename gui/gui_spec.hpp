#pragma once

#include <vector>
#include <utility>
#include <string>

namespace gui {

    using uint = unsigned int;

    enum class InputType {
        None,
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

        std::vector<position> snake;
        position food;

    };

    static const auto WINDOW_WIDTH = 1920u;
    static const auto WINDOW_HEIGHT = 1080u;
    static const std::string WINDOW_TITLE_PREFIX = "Nibbler ";

}
