#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "spec.hpp"

class SDLCanvas: public gui::Canvas {

public:
                        SDLCanvas(unsigned width, unsigned height);
    virtual             ~SDLCanvas(void);

    virtual void        setVisible(bool visible);
    virtual void        draw(const gui::GameInfo & info);
    virtual gui::Inputs getInputs(void);

private:
    void                drawTexture(int x, int y, SDL_Texture * texture);

    float               boxWidth_, boxHeight_;

    SDL_Window          *window_;
    SDL_Renderer        *renderer_;
    SDL_Texture         *spSnake_, *spFood_;

                        SDLCanvas(void);
                        SDLCanvas(const SDLCanvas &);
    SDLCanvas &         operator=(const SDLCanvas &);

};

