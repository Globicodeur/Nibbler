#pragma once

#include <SFML/network.hpp>

#include "spec.hpp"

sf::Packet & operator<<(sf::Packet & p, const Position & pos);
sf::Packet & operator>>(sf::Packet & p, Position & pos);
sf::Packet & operator<<(sf::Packet & p, const Direction & dir);
sf::Packet & operator>>(sf::Packet & p, Direction & dir);
sf::Packet & operator<<(sf::Packet & p, const network::GameInfo & info);
sf::Packet & operator>>(sf::Packet & p, network::GameInfo & info);
sf::Packet & operator<<(sf::Packet & p, const network::GameInfo::Snake & snake);
sf::Packet & operator>>(sf::Packet & p, network::GameInfo::Snake & snake);

template <class T> sf::Packet & operator<<(sf::Packet & p, const std::vector<T> & v);
template <class T> sf::Packet & operator>>(sf::Packet & p, std::vector<T> & v);
