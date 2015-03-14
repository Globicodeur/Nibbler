#include <memory>

#include "window.hpp"

#include "../gui_spec.hpp"

struct KeyBind {
    sf::Keyboard::Key key;
    gui::InputType type;
};

static const KeyBind KEY_MAP[] = {
    { sf::Keyboard::Up,      gui::InputType::Up         },
    { sf::Keyboard::Down,    gui::InputType::Down       },
    { sf::Keyboard::Left,    gui::InputType::Left       },
    { sf::Keyboard::Right,   gui::InputType::Right      },
    { sf::Keyboard::Escape,  gui::InputType::Exit       },
    { sf::Keyboard::Numpad1, gui::InputType::ChangeGui1 },
    { sf::Keyboard::Numpad2, gui::InputType::ChangeGui2 },
    { sf::Keyboard::Numpad3, gui::InputType::ChangeGui3 },
};

static std::unique_ptr<Window> window;

extern "C" {

    void init(uint width, uint height) {
        window.reset(new Window { width, height });
    }

    void clean() {
        window->close();
    }

    void draw(const gui::GameInfo & info) {
        window->processEvents();
        window->clear();
        window->render(info);
        window->display();
    }

    gui::InputType getInput() {
        if (window->isClosed())
            return gui::InputType::Exit;

        for (const auto & bind: KEY_MAP)
            if (sf::Keyboard::isKeyPressed(bind.key))
                return bind.type;
        return gui::InputType::None;
    }

}
