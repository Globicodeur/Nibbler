#pragma once

#include "Sprite.hpp"

#include "spec.hpp"

class SDLCanvas: public gui::Canvas {

public:
                        SDLCanvas(unsigned width, unsigned height);
    virtual             ~SDLCanvas(void);

    // 42 norme
                        SDLCanvas(void)                 = delete;
                        SDLCanvas(const SDLCanvas &)    = delete;
    SDLCanvas &         operator=(const SDLCanvas &)    = delete;
    //

    virtual void        draw(const gui::GameState & info);
    virtual gui::Inputs getInputs(void);

private:
    struct GraphicSnake { Sprite head, body; };
    using GraphicSnakes = std::vector<std::unique_ptr<GraphicSnake>>;
    using SpritePtr     = std::unique_ptr<Sprite>;

    void                drawSprite(int x, int y, const Sprite & sprite);
    void                drawBackground(void);

    float               boxWidth_, boxHeight_;

    SDL_Window          *window_;
    SDL_Renderer        *renderer_;
    SpritePtr           food_, background_;
    GraphicSnakes       snakes_;
};
