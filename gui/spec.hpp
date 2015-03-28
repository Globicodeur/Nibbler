#pragma once

#include <vector>
#include <string>

#include "../tools/Position.hpp"

namespace gui {

    static const auto WINDOW_WIDTH = 1920u;
    static const auto WINDOW_HEIGHT = 1080u;
    static const std::string WINDOW_TITLE_PREFIX = "Nibbler ";

    enum InputType {
        Up,
        Down,
        Left,
        Right,
        ChangeGui1,
        ChangeGui2,
        ChangeGui3,
        Exit,
    };

    using Inputs = std::vector<InputType>;

    struct GameInfo {
        std::vector<Position> snake;
        Position food;
    };

    struct Canvas {

        virtual             ~Canvas(void)           = default;

        virtual void        setVisible(bool)        = 0;
        virtual void        draw(const GameInfo &)  = 0;
        virtual Inputs      getInputs(void)         = 0;

    };

    using CanvasGetter = Canvas * (*)(unsigned, unsigned);
    static constexpr char CANVAS_GETTER_FUNC_NAME[] = "get";

}
