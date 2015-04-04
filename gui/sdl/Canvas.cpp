#include "Canvas.hpp"

#include <unordered_map>
#include <iterator>

SDLCanvas::SDLCanvas(unsigned width, unsigned height):
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height } {

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    IMG_Init(IMG_INIT_PNG);

    window_ = SDL_CreateWindow(
        (gui::WINDOW_TITLE_PREFIX + "SDL").c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        gui::WINDOW_WIDTH,
        gui::WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);

    spHead_ = IMG_LoadTexture(renderer_, "gui/sdl/assets/pedobear.png");
    spBody_ = IMG_LoadTexture(renderer_, "gui/sdl/assets/shinobu.png");
    spFood_ = IMG_LoadTexture(renderer_, "gui/sdl/assets/shinobu.png");
}

SDLCanvas::~SDLCanvas() {
    SDL_DestroyTexture(spHead_);
    SDL_DestroyTexture(spBody_);
    SDL_DestroyTexture(spFood_);
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();
}

void SDLCanvas::drawTexture(int x, int y, SDL_Texture * texture) {
    SDL_Rect rect {
        static_cast<int>(x * boxWidth_),
        static_cast<int>(y * boxHeight_),
        static_cast<int>(boxWidth_),
        static_cast<int>(boxHeight_)
    };
    SDL_RenderCopy(renderer_, texture, 0, &rect);
}

void SDLCanvas::draw(const gui::GameInfo & info) {
    SDL_RenderClear(renderer_);

    drawTexture(info.food.x, info.food.y, spFood_);
    for (const auto & snake: info.snakes) {
        drawTexture(snake.front().x, snake.front().y, spHead_);
        for (auto it = std::next(snake.begin()); it != snake.end(); ++it)
            drawTexture(it->x, it->y, spBody_);
    }

    SDL_RenderPresent(renderer_);
}

using KeyMap = std::unordered_map<SDL_Keycode, gui::InputType>;
static const KeyMap KEY_MAP = {
    { SDLK_UP,     gui::InputType::Up         },
    { SDLK_DOWN,   gui::InputType::Down       },
    { SDLK_LEFT,   gui::InputType::Left       },
    { SDLK_RIGHT,  gui::InputType::Right      },
    { SDLK_w,      gui::InputType::W          },
    { SDLK_s,      gui::InputType::S          },
    { SDLK_a,      gui::InputType::A          },
    { SDLK_d,      gui::InputType::D          },
    { SDLK_ESCAPE, gui::InputType::Exit       },
    { SDLK_1,      gui::InputType::ChangeGui1 },
    { SDLK_2,      gui::InputType::ChangeGui2 },
    { SDLK_3,      gui::InputType::ChangeGui3 },
};

gui::Inputs SDLCanvas::getInputs(void) {
    gui::Inputs inputs;
    SDL_Event event;
    KeyMap::const_iterator inputIt;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                inputs.push_back(gui::InputType::Exit);
                break ;
            case SDL_KEYDOWN:
                inputIt = KEY_MAP.find(event.key.keysym.sym);
                if (inputIt != KEY_MAP.end())
                    inputs.push_back(inputIt->second);
                break ;
            default:
                break ;
        }
    }
    return inputs;
}
