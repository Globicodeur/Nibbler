#pragma once

#include <vector>

#include "tools/Position.hpp"
#include "tools/Direction.hpp"

class Snake {

public:
    using Body              = std::vector<Position>;

                            Snake(const Body & init, bool isPlayer);
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

    void                    die(void);

private:
    Body                    body_;
    Direction               direction_, nextDirection_;
    bool                    isAlive_;
    bool                    isPlayer_;
};
