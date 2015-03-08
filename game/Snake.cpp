#include "Snake.hpp"
#include "GameEngine.hpp"

Snake::Snake(uint height, uint width): direction_(UP) {
    for (uint i = 0; i < 4; ++i)
        body_.emplace_back(width / 2 - 1, height / 2 - 1 + i);
}

Snake::~Snake(void) {

}

using std::placeholders::_1;
const Snake::MoveFn Snake::MOVERS[] =
{
    std::bind(&Snake::movedHead, _1, 0, -1),
    std::bind(&Snake::movedHead, _1, 1, 0),
    std::bind(&Snake::movedHead, _1, 0, 1),
    std::bind(&Snake::movedHead, _1, -1, 0),
};

const Position &        Snake::head() const {
    return body_.front();
}

const Snake::Body &     Snake::body() const {
    return body_;
}

void        Snake::move() {
    body_.pop_back();
    body_.insert(body_.begin(), MOVERS[direction_](this));
}

void        Snake::eat() {
    body_.push_back(body_.back());
}

Position    Snake::movedHead(int dx, int dy) const {
    return {
        head().x + dx,
        head().y + dy
    };
}

void        Snake::changeDirection(eDirection dirChange) {
    if ((direction_ == DOWN || direction_ == UP) && (dirChange == RIGHT || dirChange == LEFT))
        direction_ = dirChange;
    if ((direction_ == LEFT || direction_ == RIGHT) && (dirChange == UP || dirChange == DOWN))
        direction_ = dirChange;
}
