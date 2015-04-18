#include "packets.hpp"

sf::Packet & operator<<(sf::Packet & p, const Position & pos) {
    p << pos.x << pos.y;
    return p;
}

sf::Packet & operator>>(sf::Packet & p, Position & pos) {
    p >> pos.x >> pos.y;
    return p;
}

sf::Packet & operator<<(sf::Packet & p, const gui::GameState & info) {
    p << info.food;
    p << info.snakes;
    return p;
}

sf::Packet & operator>>(sf::Packet & p, gui::GameState & info) {
    p >> info.food;
    p >> info.snakes;
    return p;
}

sf::Packet & operator<<(sf::Packet & p, const gui::GameState::Snake & snake) {
    p << snake.id;
    p << snake.body;
    return p;
}

sf::Packet & operator>>(sf::Packet & p, gui::GameState::Snake & snake) {
    p >> snake.id;
    p >> snake.body;
    return p;
}
