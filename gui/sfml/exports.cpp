#include "Canvas.hpp"

// struct KeyBind {
//     sf::Keyboard::Key key;
//     gui::InputType type;
// };

// static const KeyBind KEY_MAP[] = {
//     { sf::Keyboard::Up,     gui::InputType::Up         },
//     { sf::Keyboard::Down,   gui::InputType::Down       },
//     { sf::Keyboard::Left,   gui::InputType::Left       },
//     { sf::Keyboard::Right,  gui::InputType::Right      },
//     { sf::Keyboard::Escape, gui::InputType::Exit       },
//     { sf::Keyboard::Num1,   gui::InputType::ChangeGui1 },
//     { sf::Keyboard::Num2,   gui::InputType::ChangeGui2 },
//     { sf::Keyboard::Num3,   gui::InputType::ChangeGui3 },
// };

// static std::unique_ptr<Window> window;

extern "C" {

    // void init(unsigned width, unsigned height) {
    //     window.reset(new Window { width, height });
    // }

    // void clean() {
    //     window->close();
    //     window.reset();
    // }

    // void draw(const gui::GameInfo & info) {
    //     window->clear();
    //     window->render(info);
    //     window->display();
    // }

    // gui::InputType getInput() {
    //     for (const auto & bind: KEY_MAP)
    //         if (sf::Keyboard::isKeyPressed(bind.key))
    //             return bind.type;
    //     return gui::InputType::None;
    // }

    gui::Canvas * get(unsigned width, unsigned height) {
        return new SFMLCanvas { width, height };
    }

}
