#include "Canvas.hpp"

#include <unordered_map>

SFMLCanvas::SFMLCanvas(unsigned width, unsigned height):
    window_ {
        sf::VideoMode {
            gui::WINDOW_WIDTH,
            gui::WINDOW_HEIGHT
        },
        gui::WINDOW_TITLE_PREFIX + "SFML"
    },
    boxWidth_ { (float)gui::WINDOW_WIDTH / width },
    boxHeight_ { (float)gui::WINDOW_HEIGHT / height } {

    snakeImg_.create(1, 1, sf::Color::Green);
    foodImg_.create(1, 1, sf::Color::Yellow);

    snakeTx_.loadFromImage(snakeImg_);
    foodTx_.loadFromImage(foodImg_);

    snakeSp_.setTexture(snakeTx_);
    foodSp_.setTexture(foodTx_);

    snakeSp_.scale(boxWidth_, boxHeight_);
    foodSp_.scale(boxWidth_, boxHeight_);
}

void SFMLCanvas::draw(const gui::GameInfo & info) {
    window_.clear();

    foodSp_.setPosition(
        info.food.x * boxWidth_,
        info.food.y * boxHeight_
    );
    window_.draw(foodSp_);

    for (auto bodyPart: info.snake) {
        snakeSp_.setPosition(
            bodyPart.x * boxWidth_,
            bodyPart.y * boxHeight_
        );
        window_.draw(snakeSp_);
    }

    window_.display();
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
