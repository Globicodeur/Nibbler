#pragma once

#include <vector>
#include <utility>
#include <string>

using uint = unsigned int;

namespace gui {

    enum InputType {
        Up,
        Down,
        Left,
        Right,
        ChangeGui1,
        ChangeGui2,
        ChangeGui3,
        Exit,
        None,
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
