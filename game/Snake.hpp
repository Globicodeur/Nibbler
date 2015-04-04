#pragma once

#include <vector>

#include "tools/Position.hpp"
#include "tools/Direction.hpp"

class Snake {

public:
    using Body              = std::vector<Position>;

                            Snake(const Body & init);
                            ~Snake(void) = default;

    void                    eat(void);
    void                    move(void);
    void                    turn(Direction newDirection);
    void                    setHeadPosition(const Position & pos);

    bool                    isAlive(void) const;
    void                    die(void);

    const Position &        head(void) const;
    const Body &            body(void) const;

private:
    Body                    body_;
    Direction               direction_, nextDirection_;
    bool                    isAlive_;

    static const Position   DELTAS[];

                            Snake(void);
                            // Snake(const Snake &);
    // Snake &                 operator=(const Snake &);
};
