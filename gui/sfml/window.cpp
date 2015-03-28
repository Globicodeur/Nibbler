#include "window.hpp"

#include "../gui_spec.hpp"

Window::Window(unsigned width, unsigned height):
    sf::RenderWindow {
        sf::VideoMode { gui::WINDOW_WIDTH, gui::WINDOW_HEIGHT },
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

void Window::render(const gui::GameInfo & info) {
    foodSp_.setPosition(
        info.food.first * boxWidth_,
        info.food.second * boxHeight_
    );
    draw(foodSp_);

    for (const auto & pos: info.snake) {
        snakeSp_.setPosition(
            pos.first * boxWidth_,
            pos.second * boxHeight_
        );
        draw(snakeSp_);
    }
}
