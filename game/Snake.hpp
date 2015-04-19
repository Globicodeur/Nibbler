#pragma once

#include <vector>

#include "tools/Position.hpp"
#include "tools/Direction.hpp"

class Snake {

public:
    using Body              = std::vector<Position>;

                            Snake(const Body &, bool, Direction, unsigned);
    // 42 norme
                            ~Snake(void)                = default;
                            Snake(void)                 = delete;
                            Snake(const Snake &)        = default;
    Snake &                 operator=(const Snake &)    = delete;
    //

    void                    move(void);
    void                    eat(void);
    void                    turn(Direction newDirection);
    void                    setHeadPosition(const Position & pos);

    bool                    isAlive(void) const;
    bool                    isPlayer(void) const;
    const Position &        head(void) const;
    const Body &            body(void) const;
    Direction               direction(void) const;
    unsigned                id(void) const;

    void                    die(void);
    void                    installAi(void);

private:
    Body                    body_;
    Direction               direction_, nextDirection_;
    bool                    isAlive_;
    bool                    isPlayer_;
    unsigned                id_;
};
