#pragma once

#include "nibbler.hpp"

using position = std::pair<uint, uint>;

class GameEngine;

class Snake {

public:
    uint                    gameHeight;
    uint                    gameWidth;
    std::vector<position>   body;
    eDirection              direction;

                            Snake(uint height, uint width);
                            ~Snake(void);
    bool                    move(GameEngine &game);
    int                     checkCollisions(position &food);

private:
    typedef bool (Snake::*MoveFn)(position &, position &);
    static const MoveFn MOVERS[];

                            Snake(void) = default;
                            Snake(const Snake &copy) = default;
    Snake &                 operator=(const Snake &copy) = default;


    bool                    moveUp(position &newHead, position &oldHead);
    bool                    moveRight(position &newHead, position &oldHead);
    bool                    moveDown(position &newHead, position &oldHead);
    bool                    moveLeft(position &newHead, position &oldHead);
};
