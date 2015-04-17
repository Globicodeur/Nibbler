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

sf::Packet & operator<<(sf::Packet & p, const network::GameInfo::Snake & snake) {
    p << snake.id;
    p << snake.body;
    return p;
}

sf::Packet & operator>>(sf::Packet & p, network::GameInfo::Snake & snake) {
    p >> snake.id;
    p >> snake.body;
    return p;
}

template <class T>
sf::Packet & operator>>(sf::Packet & p, std::vector<T> & v) {
    sf::Uint64 size;
    p >> size;
    v.resize(size);
    for (sf::Uint64 i = 0; i < size; ++i)
        p >> v[i];
    return p;
}

template <class T>
sf::Packet & operator<<(sf::Packet & p, const std::vector<T> & v) {
    p << static_cast<sf::Uint64>(v.size());
    for (const auto & t: v)
        p << t;
    return p;
}
