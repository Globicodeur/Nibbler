#pragma once

#include "nibbler.hpp"
#include "Position.hpp"

class Snake {

public:
    using Body = std::vector<Position>;

                            Snake(uint height, uint width);
                            ~Snake(void);
    void                    move();
    void                    changeDirection(eDirection dirChange);

    const Position &        head() const;
    const Body &            body() const;
    void                    eat();

private:
    typedef std::function<Position (Snake *)> MoveFn;
    static const MoveFn MOVERS[];

                            Snake(void) = default;
                            Snake(const Snake &copy) = default;
    Snake &                 operator=(const Snake &copy) = default;

    Position                movedHead(int dx, int dy) const;

    Body                    body_;
    eDirection              direction_;
    bool                    hasChanged_;
};
