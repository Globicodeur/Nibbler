#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace gui { struct GameInfo; }

class Window {

public:
    SDL_Window      *win;
    SDL_Renderer    *renderer;
    SDL_Surface     *surface;
    SDL_Surface     *surface_snake;
    SDL_Surface     *surface_doge;
    SDL_Event       event;

                    Window(uint width, uint height);
                    ~Window();
    bool            isClosed(void) const;
    void            processEvents(void);
    void            clear(void) const;
    void            render(const gui::GameInfo &info);
    void            display(void) const;
    float           getBoxWidth(void) const;
    float           getBoxHeight(void) const;

private:
    float           boxWidth_, boxHeight_;
    bool            isClosed_;

};
