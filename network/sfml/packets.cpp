#include "packets.hpp"

sf::Packet & operator<<(sf::Packet & p, const Position & pos) {
    p << pos.x << pos.y;
    return p;
}

sf::Packet & operator>>(sf::Packet & p, Position & pos) {
    p >> pos.x >> pos.y;
    return p;
}

sf::Packet & operator<<(sf::Packet & p, const Direction & dir) {
    return p << static_cast<int>(dir);
}

sf::Packet & operator>>(sf::Packet & p, Direction & dir) {
    int raw;
    p >> raw;
    dir = static_cast<Direction>(raw);
    return p;
}

sf::Packet & operator<<(sf::Packet & p, const network::GameInfo & info) {
    p << info.food;
    p << info.snakes;
    return p;
}

sf::Packet & operator>>(sf::Packet & p, network::GameInfo & info) {
    p >> info.food;
    p >> info.snakes;
    return p;
}
