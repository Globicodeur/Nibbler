#pragma once

#include <functional>
#include <vector>

#include "Position.hpp"
#include "Direction.hpp"

class Snake {

public:
    using Body = std::vector<Position>;

                            Snake(uint height, uint width);
                            ~Snake(void);

    void                    eat();
    void                    move();
    void                    changeDirection(Direction dirChange);

    const Position &        head() const;
    const Body &            body() const;

private:

    using MoveFn = std::function<Position (Snake *)>;
    static const MoveFn MOVERS[];

                            Snake(void) = default;
                            Snake(const Snake &copy) = default;
    Snake &                 operator=(const Snake &copy) = default;

    Position                movedHead(int dx, int dy) const;

    Body                    body_;
    Direction               direction_;
    bool                    hasChanged_;
};
