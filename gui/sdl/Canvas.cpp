#include "Canvas.hpp"

#include <unordered_map>
#include <iterator>

static const std::string SPRITES_PATH_PREFIX = "gui/sdl/assets/";

static const std::string SPRITES[][2] = {
    { { "pedobear_1.png" }, { "shinobu_1.png" } },
    { { "pedobear_2.png" }, { "shinobu_2.png" } },
    { { "pedobear_3.png" }, { "shinobu_3.png" } },
    { { "pedobear_4.png" }, { "shinobu_4.png" } },
};

SDLCanvas::SDLCanvas(unsigned width, unsigned height):
    boxWidth_   { (float)gui::WINDOW_WIDTH / width },
    boxHeight_  { (float)gui::WINDOW_HEIGHT / height } {

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

    food_.reset(new Sprite { SPRITES_PATH_PREFIX + "shinobu.png", renderer_ });
    background_.reset(new Sprite { SPRITES_PATH_PREFIX + "sakura.png", renderer_ });
    obstacle_.reset(new Sprite { SPRITES_PATH_PREFIX + "???.png", renderer_ });

    for (auto spritePair: SPRITES)
        snakes_.emplace_back(new GraphicSnake {
            { SPRITES_PATH_PREFIX + spritePair[0], renderer_ },
            { SPRITES_PATH_PREFIX + spritePair[1], renderer_ },
        });
}

SDLCanvas::~SDLCanvas() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    IMG_Quit();
    SDL_Quit();
}

void SDLCanvas::drawSprite(const Position & pos, const Sprite & sprite) {
    SDL_Rect rect {
        static_cast<int>(pos.x * boxWidth_),
        static_cast<int>(pos.y * boxHeight_),
        static_cast<int>(boxWidth_),
        static_cast<int>(boxHeight_)
    };
    SDL_RenderCopy(renderer_, sprite.texture(), 0, &rect);
}

void SDLCanvas::drawBackground(void) {
    static SDL_Rect rect { 0, 0, gui::WINDOW_WIDTH, gui::WINDOW_WIDTH };
    SDL_RenderCopy(renderer_, background_->texture(), 0, &rect);
}

void SDLCanvas::draw(const gui::GameState & info) {
    SDL_RenderClear(renderer_);

    drawBackground();
    drawSprite(info.food, *food_);
    for (const auto & obstacle: info.obstacles)
        drawSprite(obstacle, *obstacle_);
    for (const auto & snake: info.snakes) {
        auto & graphicSnake = snakes_[snake.id % snakes_.size()];
        drawSprite(snake.body.front(), graphicSnake->head);
        for (auto it = std::next(snake.body.begin()); it != snake.body.end(); ++it)
            drawSprite(*it, graphicSnake->body);
    }

    SDL_RenderPresent(renderer_);
}

using KeyMap = std::unordered_map<SDL_Keycode, gui::Input>;
static const KeyMap KEY_MAP = {
    { SDLK_UP,     gui::Input::Up    },
    { SDLK_DOWN,   gui::Input::Down  },
    { SDLK_LEFT,   gui::Input::Left  },
    { SDLK_RIGHT,  gui::Input::Right },
    { SDLK_w,      gui::Input::W     },
    { SDLK_s,      gui::Input::S     },
    { SDLK_a,      gui::Input::A     },
    { SDLK_d,      gui::Input::D     },
    { SDLK_ESCAPE, gui::Input::Exit  },
    { SDLK_1,      gui::Input::Key1  },
    { SDLK_2,      gui::Input::Key2  },
    { SDLK_3,      gui::Input::Key3  },
};

gui::Inputs SDLCanvas::getInputs(void) {
    gui::Inputs inputs;
    SDL_Event event;
    KeyMap::const_iterator inputIt;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                inputs.push_back(gui::Input::Exit);
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
