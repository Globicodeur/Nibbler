#include "Snake.hpp"
#include "GameEngine.hpp"

static const auto SNAKE_INITIAL_SIZE = 4u;

Snake::Snake(unsigned height, unsigned width):
    direction_ { UP },
    canChangDirection_ { true } {

    for (unsigned i = 0; i < SNAKE_INITIAL_SIZE; ++i)
        body_.emplace_back(width / 2 - 1, height / 2 - 1 + i);
}

const Position Snake::DELTAS[] = {
    { 0, -1 },
    { 0,  1 },
    { -1, 0 },
    { 1,  0 },
};

const Position & Snake::head() const {
    return body_.front();
}

const Snake::Body & Snake::body() const {
    return body_;
}

void Snake::move() {
    body_.pop_back();
    body_.insert(body_.begin(), head() + DELTAS[direction_]);
    canChangDirection_ = true;
}

void Snake::eat() {
    body_.push_back(body_.back());
}

void Snake::changeDirection(Direction newDirection) {
    if (canChangDirection_ && newDirection != OPPOSITES[direction_]) {
        direction_ = newDirection;
        canChangDirection_ = false;
    }
}
