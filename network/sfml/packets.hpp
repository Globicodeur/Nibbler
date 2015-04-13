#pragma once

#include <SFML/network.hpp>

#include "spec.hpp"

sf::Packet & operator<<(sf::Packet & p, const Position & pos);
sf::Packet & operator>>(sf::Packet & p, Position & pos);
sf::Packet & operator<<(sf::Packet & p, const Direction & dir);
sf::Packet & operator>>(sf::Packet & p, Direction & dir);
sf::Packet & operator<<(sf::Packet & p, const network::GameInfo & info);
sf::Packet & operator>>(sf::Packet & p, network::GameInfo & info);

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
