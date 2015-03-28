#include "Position.hpp"

Position::Position(int x, int y):
    x(x), y(y)
{ }

Position Position::operator+(const Position & delta) const {
    return {
        x + delta.x,
        y + delta.y
    };
}

bool operator==(const Position & lhs, const Position & rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
