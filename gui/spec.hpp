#pragma once

#include <vector>
#include <string>

#include "../tools/Position.hpp"

namespace gui {

    static const auto WINDOW_WIDTH = 1920u;
    static const auto WINDOW_HEIGHT = 1080u;
    static const std::string WINDOW_TITLE_PREFIX = "Nibbler ";

    enum class Input {
        Up,
        Down,
        Left,
        Right,
        W,
        S,
        A,
        D,
        Key1,
        Key2,
        Key3,
        Exit,
    };

    using Inputs = std::vector<Input>;

    struct GameInfo {
        struct Snake {
            using Body = std::vector<Position>;

            unsigned id;
            Body body;
        };
        using Snakes = std::vector<Snake>;

        Snakes snakes;
        Position food;
    };

    struct Canvas {

        // Dependent type for SharedObject usability
        struct SharedObjectInfo {
            using Getter = Canvas * (*)(unsigned, unsigned);
            static constexpr const char * getterName() { return "get"; };
        };

        virtual             ~Canvas(void)           = default;

        virtual void        draw(const GameInfo &)  = 0;
        virtual Inputs      getInputs(void)         = 0;

    };

}
