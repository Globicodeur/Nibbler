#include <memory>

#include "window.hpp"

#include "../gui_spec.hpp"

struct KeyBind {
    SDL_Keycode        key;
    gui::InputType     type;
};

static const KeyBind KEY_MAP[] = {
    { SDLK_UP,     gui::InputType::Up         },
    { SDLK_DOWN,   gui::InputType::Down       },
    { SDLK_LEFT,   gui::InputType::Left       },
    { SDLK_RIGHT,  gui::InputType::Right      },
    { SDLK_ESCAPE, gui::InputType::Exit       },
    { SDLK_KP_1,   gui::InputType::ChangeGui1 },
    { SDLK_KP_2,   gui::InputType::ChangeGui2 },
    { SDLK_KP_3,   gui::InputType::ChangeGui3 },
};

static std::unique_ptr<Window> window;

extern "C" {

    void init(unsigned width, unsigned height) {
        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
        window.reset(new Window { width, height });
    }

    void clean() {
        SDL_Quit();
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

        SDL_PollEvent(&window->event);
        if (window->event.type == SDL_KEYDOWN) {
            for (const auto & bind: KEY_MAP)
                if (window->event.key.keysym.sym == bind.key)
                {
                    window->event.key.keysym.sym = 0;
                    return bind.type;
                }
        }

        window->event.key.keysym.sym = 0;
        return gui::InputType::None;
    }

}
