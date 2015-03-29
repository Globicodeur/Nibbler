#pragma once

// This is workaround for the norme: we should not be forced to implement things
// in a source file because it just kills optimization and therefore performance
template <class T>
class PositionT {

public:
    T           x, y;

                PositionT(void) = default;
                ~PositionT(void) = default;

                PositionT(int x, int y):
                    x(x), y(y)
                { }

                PositionT(const PositionT &) = default;
    PositionT & operator=(const PositionT &) = default;

    PositionT   operator+(const PositionT & delta) const {
        return {
            x + delta.x,
            y + delta.y
        };
    }
};

template <class T>
bool operator==(const PositionT<T> & lhs, const PositionT<T> & rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

using Position = PositionT<int>;
