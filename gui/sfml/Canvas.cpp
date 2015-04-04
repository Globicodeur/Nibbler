#include "Canvas.hpp"

#include <unordered_map>
#include <iterator>

SFMLCanvas::SFMLCanvas(unsigned width, unsigned height):
    window_ {
        sf::VideoMode {
            gui::WINDOW_WIDTH,
            gui::WINDOW_HEIGHT
        },
        gui::WINDOW_TITLE_PREFIX + "SFML",
        sf::Style::Titlebar | sf::Style::Close
    },
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height } {

    headImg_.create(1, 1, sf::Color { 32, 128, 32 });
    bodyImg_.create(1, 1, sf::Color::Green);
    foodImg_.create(1, 1, sf::Color::Yellow);

    headTx_.loadFromImage(headImg_);
    bodyTx_.loadFromImage(bodyImg_);
    foodTx_.loadFromImage(foodImg_);

    headSp_.setTexture(headTx_);
    bodySp_.setTexture(bodyTx_);
    foodSp_.setTexture(foodTx_);

    headSp_.scale(boxWidth_, boxHeight_);
    bodySp_.scale(boxWidth_, boxHeight_);
    foodSp_.scale(boxWidth_, boxHeight_);
}

void SFMLCanvas::draw(const gui::GameInfo & info) {
    window_.clear();

    drawSpriteAt(info.food, foodSp_);
    drawSpriteAt(info.snake.front(), headSp_);

    for (auto it = std::next(info.snake.begin()); it != info.snake.end(); ++it)
        drawSpriteAt(*it, bodySp_);

    window_.display();
}

void SFMLCanvas::drawSpriteAt(const Position & pos, sf::Sprite & sprite) {
    sprite.setPosition(
        pos.x * boxWidth_,
        pos.y * boxHeight_
    );
    window_.draw(sprite);
}

using KeyMap = std::unordered_map<sf::Keyboard::Key, gui::InputType>;
static const KeyMap KEY_MAP = {
    { sf::Keyboard::Up,     gui::InputType::Up         },
    { sf::Keyboard::Down,   gui::InputType::Down       },
    { sf::Keyboard::Left,   gui::InputType::Left       },
    { sf::Keyboard::Right,  gui::InputType::Right      },
    { sf::Keyboard::Escape, gui::InputType::Exit       },
    { sf::Keyboard::Num1,   gui::InputType::ChangeGui1 },
    { sf::Keyboard::Num2,   gui::InputType::ChangeGui2 },
    { sf::Keyboard::Num3,   gui::InputType::ChangeGui3 },
};

gui::Inputs SFMLCanvas::getInputs(void) {
    gui::Inputs inputs;
    sf::Event event;
    KeyMap::const_iterator inputIt;

    while (window_.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                inputs.push_back(gui::InputType::Exit);
                break ;
            case sf::Event::KeyPressed:
                inputIt = KEY_MAP.find(event.key.code);
                if (inputIt != KEY_MAP.end())
                    inputs.push_back(inputIt->second);
                break ;
            default:
                break ;
        }
    }
    return inputs;
}
