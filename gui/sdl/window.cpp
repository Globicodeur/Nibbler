#include "window.hpp"

#include "../gui_spec.hpp"

Window::Window(uint width, uint height):
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height },
    isClosed_ { false } {
    win = SDL_CreateWindow(
        "SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        gui::WINDOW_WIDTH,
        gui::WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    surface = SDL_CreateRGBSurface(0, boxWidth_, boxHeight_, 32, 0, 0, 0, 255);
    surface_doge = SDL_LoadBMP("gui/doge.bmp");
    surface_snake = SDL_LoadBMP("gui/snake.bmp");
}

Window::~Window() {
    SDL_FreeSurface(surface);
    SDL_FreeSurface(surface_doge);
    SDL_FreeSurface(surface_snake);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
}

bool            Window::isClosed() const {
    return isClosed_;
}

void            Window::processEvents() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            isClosed_ = true;
    }
}

void            Window::clear(void) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

static void     renderSquare(int x, int y, int sprite, Window *window) {
    int             w, h;
    SDL_Texture     *texture;

    // SDL_FillRect(window->surface, 0, color);
    if (sprite)
        texture = SDL_CreateTextureFromSurface(window->renderer, window->surface_doge);
    else
        texture = SDL_CreateTextureFromSurface(window->renderer, window->surface_snake);
    SDL_QueryTexture(texture, 0, 0, &w, &h);
    SDL_Rect    rect = {x, y, static_cast<int>(window->getBoxWidth()), static_cast<int>(window->getBoxHeight())};
    SDL_RenderCopy(window->renderer, texture, 0, &rect);
    SDL_DestroyTexture(texture);
}

void            Window::render(const gui::GameInfo &info) {
    // uint        color;

    // color = SDL_MapRGB(surface->format, 255, 255, 0);
    renderSquare(info.food.first * boxWidth_, info.food.second * boxHeight_, 0, this);
    // color = SDL_MapRGB(surface->format, 0, 255, 0);
    for (const auto & pos: info.snake) {
        renderSquare(pos.first * boxWidth_, pos.second * boxHeight_, 1, this);
    }
}


void            Window::display(void) const {
    SDL_RenderPresent(renderer);
}

float           Window::getBoxWidth(void) const {
    return boxWidth_;
}

float           Window::getBoxHeight(void) const {
    return boxHeight_;
}
