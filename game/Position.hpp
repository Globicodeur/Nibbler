#pragma once

class Position {

public:
    int         x, y;

                Position(void) = default;
                ~Position(void) = default;
                Position(int x, int y);
                Position(const Position &) = default;
    Position &  operator=(const Position &) = default;

    Position    operator+(const Position &) const;
};

bool operator==(const Position & lhs, const Position & rhs);
