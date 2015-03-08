#include "Position.hpp"

Position::Position(int x, int y):
    x(x), y(y)
{ }

bool operator==(const Position & lhs, const Position & rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
