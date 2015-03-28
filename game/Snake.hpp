#pragma once

#include <functional>
#include <vector>

#include "Position.hpp"
#include "Direction.hpp"

class Snake {

public:
    using Body = std::vector<Position>;

                            Snake(unsigned height, unsigned width);
                            ~Snake(void);

    void                    eat();
    void                    move();
    void                    changeDirection(Direction dirChange);

    const Position &        head() const;
    const Body &            body() const;

private:
                            Snake(void) = default;
                            Snake(const Snake &copy) = default;
    Snake &                 operator=(const Snake &copy) = default;


    Body                    body_;
    Direction               direction_;
    bool                    hasChanged_;
    static const Position   DELTAS[];
};
