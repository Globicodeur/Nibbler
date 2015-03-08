#include "Snake.hpp"
#include "GameEngine.hpp"

static std::vector<position>        createBody(uint y, uint x) {
    std::vector<position>   body;

    for (uint i = 0; i < 4; ++i) {
        position    part;
        part = std::make_pair(y + i, x);
        body.push_back(part);
    }

    return body;
}

Snake::Snake(uint height, uint width): gameHeight(height), gameWidth(width) {
    body = createBody(height / 2 - 1, width / 2 - 1);
    direction = UP;
}

Snake::~Snake(void) {

}

const Snake::MoveFn Snake::MOVERS[] =
{
    &Snake::moveUp,
    &Snake::moveRight,
    &Snake::moveDown,
    &Snake::moveLeft
};

int        Snake::checkCollisions(position &food) {
    std::vector<position>   snakePos = body;
    position                head = snakePos[0];

    if (std::get<0>(head) == std::get<0>(food) && std::get<1>(head) == std::get<1>(food))
        return 1;
    for (std::vector<position>::iterator i = snakePos.begin(); i != snakePos.end(); ++i) {
        if (std::get<0>(head) == std::get<0>(*i) && std::get<1>(head) == std::get<1>(*i))
            return 2;
    }
    return 0;
}

bool        Snake::move(GameEngine &game) {
    position    newHead;
    position    &oldHead = body[0];
    bool        moved = false;
    position    &food = game.food;

    if ((this->*(MOVERS[direction]))(newHead, oldHead)) {
        if (checkCollisions(food) != 1)
            body.pop_back();
        if (checkCollisions(food) == 0)
            moved = true;
        if (checkCollisions(food) == 1)
            game.spawnFood();
        body.insert(body.begin(), newHead);
    }
    return moved;
}

bool        Snake::moveUp(position &newHead, position &oldHead) {
    uint    oldY = std::get<0>(oldHead);

    if (oldY == 0)
        return false;
    newHead = std::make_pair(std::get<0>(oldHead) - 1, std::get<1>(oldHead));
    return true;
}

bool        Snake::moveRight(position &newHead, position &oldHead) {
    uint    oldX = std::get<1>(oldHead);

    if (oldX == gameWidth - 1)
        return false;
    newHead = std::make_pair(std::get<0>(oldHead), std::get<1>(oldHead) + 1);
    return true;
}

bool        Snake::moveDown(position &newHead, position &oldHead) {
    uint    oldY = std::get<0>(oldHead);

    if (oldY == gameHeight - 1)
        return false;
    newHead = std::make_pair(std::get<0>(oldHead) + 1, std::get<1>(oldHead));
    return true;
}

bool        Snake::moveLeft(position &newHead, position &oldHead) {
    uint    oldX = std::get<1>(oldHead);

    if (oldX == 0)
        return false;
    newHead = std::make_pair(std::get<0>(oldHead), std::get<1>(oldHead) - 1);
    return true;
}
