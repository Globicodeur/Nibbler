#include "Snake.hpp"

Snake::Snake(const Body & init, bool isPlayer):
    body_           { init },
    direction_      { Up },
    nextDirection_  { direction_ },
    isAlive_        { true },
    isPlayer_       { isPlayer }
{ }

void Snake::move(void) {
    static const Position deltas[] = {
    //     Up        Down      Left       Right
        { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 },
    };

    body_.pop_back();
    body_.insert(body_.begin(), head() + deltas[nextDirection_]);
    direction_ = nextDirection_;
}

void Snake::eat(void) {
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

bool Snake::isPlayer(void) const {
    return isPlayer_;
}

const Position & Snake::head(void) const {
    return body_.front();
}

const Snake::Body & Snake::body(void) const {
    return body_;
}

Direction Snake::direction(void) const {
    return direction_;
}

void Snake::die(void) {
    isAlive_ = false;
}
