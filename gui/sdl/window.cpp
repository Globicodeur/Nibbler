#include "window.hpp"

Window::Window(unsigned width, unsigned height):
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height } {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);

    win_ = SDL_CreateWindow(
        (gui::WINDOW_TITLE_PREFIX + "SDL").c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        gui::WINDOW_WIDTH,
        gui::WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderer_ = SDL_CreateRenderer(win_, -1, SDL_RENDERER_ACCELERATED);

    auto snakeSurface = SDL_LoadBMP("gui/sdl/assets/pedobear.bmp");
    spSnake_ = SDL_CreateTextureFromSurface(renderer_, snakeSurface);
    SDL_FreeSurface(snakeSurface);
    spFood_ = IMG_LoadTexture(renderer_, "gui/sdl/assets/shinobu.png");
}

Window::~Window() {
    SDL_DestroyTexture(spSnake_);
    SDL_DestroyTexture(spFood_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(win_);
    IMG_Quit();
    SDL_Quit();
}

void            Window::clear(void) const {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

void            Window::drawTexture(int x, int y, SDL_Texture * texture) {
    SDL_Rect rect {
        static_cast<int>(x * boxWidth_),
        static_cast<int>(y * boxHeight_),
        static_cast<int>(boxWidth_),
        static_cast<int>(boxHeight_)
    };
    SDL_RenderCopy(renderer_, texture, 0, &rect);
}

void            Window::render(const gui::GameInfo &info) {
    drawTexture(info.food.first, info.food.second, spFood_);
    for (auto pos: info.snake)
        drawTexture(pos.first, pos.second, spSnake_);
}


void            Window::display(void) const {
    SDL_RenderPresent(renderer_);
}

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

gui::InputType  Window::getInput(void) {
    while (SDL_PollEvent(&event_)) {
        if (event_.type == SDL_KEYDOWN) {
            for (const auto & bind: KEY_MAP) {
                if (event_.key.keysym.sym == bind.key)
                    return bind.type;
            }
        }
    }

    return gui::InputType::None;
}
