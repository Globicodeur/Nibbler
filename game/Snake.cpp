#include "Snake.hpp"
#include "GameEngine.hpp"

static const auto SNAKE_INITIAL_SIZE = 4u;
static_assert(SNAKE_INITIAL_SIZE > 0, "Snake size cannot be zero");

const Position Snake::DELTAS[] = {
    { 0, -1 },
    { 0,  1 },
    { -1, 0 },
    { 1,  0 },
};

Snake::Snake(int height, int width):
    direction_ { Up },
    nextDirection_ { direction_ } {

    for (unsigned i = 0; i < SNAKE_INITIAL_SIZE; ++i)
        body_.emplace_back(width / 2 - 1, height / 2 - 1 + i);
}

const Position & Snake::head() const {
    return body_.front();
}

const Snake::Body & Snake::body() const {
    return body_;
}

void Snake::move() {
    body_.pop_back();
    body_.insert(body_.begin(), head() + DELTAS[nextDirection_]);
    direction_ = nextDirection_;
}

void Snake::eat() {
    body_.push_back(body_.back());
}

void Snake::turn(Direction newDirection) {
    if (newDirection != OPPOSITES[direction_])
        nextDirection_ = newDirection;
}
