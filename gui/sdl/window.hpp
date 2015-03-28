#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../gui_spec.hpp"

class Window {

public:
                    Window(unsigned width, unsigned height);
                    ~Window();

    void            clear(void) const;
    void            render(const gui::GameInfo &info);
    void            display(void) const;

    gui::InputType  getInput(void);

private:
    void            drawTexture(int x, int y, SDL_Texture * texture);

    float           boxWidth_, boxHeight_;

    SDL_Window      *win_;
    SDL_Renderer    *renderer_;
    SDL_Texture     *spSnake_, *spFood_;
};
