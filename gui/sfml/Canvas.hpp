#pragma once

#include <SFML/Graphics.hpp>

#include "spec.hpp"

class SFMLCanvas: public gui::Canvas {

public:
                        SFMLCanvas(unsigned width, unsigned height);
    virtual             ~SFMLCanvas(void) = default;

    virtual void        draw(const gui::GameInfo & info);
    virtual gui::Inputs getInputs(void);

private:
    sf::RenderWindow    window_;

    float               boxWidth_, boxHeight_;

    sf::Image           headImg_, bodyImg_ , foodImg_;
    sf::Texture         headTx_, bodyTx_ , foodTx_;
    sf::Sprite          headSp_, bodySp_ , foodSp_;

    void                drawSpriteAt(const Position & pos, sf::Sprite & sprite);

                        SFMLCanvas(void);
                        SFMLCanvas(const SFMLCanvas &);
    SFMLCanvas &        operator=(const SFMLCanvas &);

};
