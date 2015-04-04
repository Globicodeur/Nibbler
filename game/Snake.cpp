#include "Snake.hpp"

const Position Snake::DELTAS[] = {
    { 0, -1 },
    { 0,  1 },
    { -1, 0 },
    { 1,  0 },
};

Snake::Snake(const Body & init):
    body_ { init },
    direction_ { Up },
    nextDirection_ { direction_ },
    isAlive_ { true }
{ }

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

void Snake::setHeadPosition(const Position & pos) {
    body_.front() = pos;
}

bool Snake::isAlive(void) const {
    return isAlive_;
}

void Snake::die(void) {
    isAlive_ = false;
}
