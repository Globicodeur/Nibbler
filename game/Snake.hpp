#pragma once

#include <functional>
#include <vector>

#include "tools/Position.hpp"
#include "tools/Direction.hpp"

class Snake {

public:
    using Body = std::vector<Position>;

                            Snake(unsigned height, unsigned width);
                            ~Snake(void) = default;

    void                    eat();
    void                    move();
    void                    changeDirection(Direction newDirection);

    const Position &        head() const;
    const Body &            body() const;

private:
                            Snake(void);
                            Snake(const Snake &);
    Snake &                 operator=(const Snake &);

    Body                    body_;
    Direction               direction_;
    bool                    canChangDirection_;

    static const Position   DELTAS[];
};
