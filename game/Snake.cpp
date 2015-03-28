#include "Snake.hpp"
#include "GameEngine.hpp"

Snake::Snake(unsigned height, unsigned width):
    direction_(UP),
    hasChanged_(false) {
    for (unsigned i = 0; i < 4; ++i)
        body_.emplace_back(width / 2 - 1, height / 2 - 1 + i);
}

Snake::~Snake(void) {

}

const Position Snake::DELTAS[] = {
    { 0, -1 },
    { 0,  1 },
    { -1, 0 },
    { 1,  0 },
};

const Position &        Snake::head() const {
    return body_.front();
}

const Snake::Body &     Snake::body() const {
    return body_;
}

void        Snake::move() {
    body_.pop_back();
    body_.insert(body_.begin(), head() + DELTAS[direction_]);
    hasChanged_ = false;
}

void        Snake::eat() {
    body_.push_back(body_.back());
}

void        Snake::changeDirection(Direction dirChange) {
    if (hasChanged_)
        return ;

    if (OPPOSITES[direction_] != dirChange) {
        direction_ = dirChange;
        hasChanged_ = true;
    }
}
