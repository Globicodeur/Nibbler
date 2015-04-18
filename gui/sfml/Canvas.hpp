#pragma once

#include "Sprite.hpp"

#include "spec.hpp"

class SFMLCanvas: public gui::Canvas {

public:
                        SFMLCanvas(unsigned width, unsigned height);

    // 42 norme
    virtual             ~SFMLCanvas(void)               = default;
                        SFMLCanvas(void)                = delete;
                        SFMLCanvas(const SFMLCanvas &)  = delete;
    SFMLCanvas &        operator=(const SFMLCanvas &)   = delete;
    //

    virtual void        draw(const gui::GameState & info);
    virtual gui::Inputs getInputs(void);

private:
    struct GraphicSnake { Sprite head, body; };
    using GraphicSnakes = std::vector<std::unique_ptr<GraphicSnake>>;

    sf::RenderWindow    window_;

    float               boxWidth_, boxHeight_;
    GraphicSnakes       snakes_;
    Sprite              food_;

    void                drawSpriteAt(const Position & pos, sf::Sprite & sprite);
};
