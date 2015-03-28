#pragma once

#include <SFML/Graphics.hpp>

#include "spec.hpp"

class SFMLCanvas: public gui::Canvas {

public:
                        SFMLCanvas(unsigned width, unsigned height);
    virtual             ~SFMLCanvas(void) = default;

    virtual void        setVisible(bool visible);
    virtual void        draw(const gui::GameInfo & info);
    virtual gui::Inputs getInputs(void);

private:
    sf::RenderWindow    window_;

    float               boxWidth_, boxHeight_;

    sf::Image           snakeImg_, foodImg_;
    sf::Texture         snakeTx_, foodTx_;
    sf::Sprite          snakeSp_, foodSp_;

                        SFMLCanvas(void);
                        SFMLCanvas(const SFMLCanvas &);
    SFMLCanvas &        operator=(const SFMLCanvas &);

};
