#include <SFML/Graphics.hpp>

#include "../gui_spec.hpp"

extern bool has_quit;

struct KeyBind {
    sf::Keyboard::Key key;
    gui::InputType type;
};

static const KeyBind KEY_MAP[] = {
    { sf::Keyboard::Up,     gui::InputType::Up         },
    { sf::Keyboard::Down,   gui::InputType::Down       },
    { sf::Keyboard::Left,   gui::InputType::Left       },
    { sf::Keyboard::Right,  gui::InputType::Right      },
    { sf::Keyboard::Escape, gui::InputType::Exit       },
    { sf::Keyboard::Num1,   gui::InputType::ChangeGui1 },
    { sf::Keyboard::Num2,   gui::InputType::ChangeGui2 },
    { sf::Keyboard::Num3,   gui::InputType::ChangeGui3 },
};

extern "C" gui::InputType getInput() {
    if (has_quit)
        return gui::InputType::Exit;

    for (const auto & bind: KEY_MAP)
        if (sf::Keyboard::isKeyPressed(bind.key))
            return bind.type;
    return gui::InputType::None;
}
