#pragma once

#include <SFML/network.hpp>

#include "spec.hpp"

sf::Packet & operator<<(sf::Packet & p, const Position & pos);
sf::Packet & operator>>(sf::Packet & p, Position & pos);
sf::Packet & operator<<(sf::Packet & p, const gui::GameState & info);
sf::Packet & operator>>(sf::Packet & p, gui::GameState & info);
sf::Packet & operator<<(sf::Packet & p, const gui::GameState::Snake & snake);
sf::Packet & operator>>(sf::Packet & p, gui::GameState::Snake & snake);

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

template <class Enum>
std::enable_if_t<std::is_enum<Enum>::value, sf::Packet &>
operator<<(sf::Packet & p, const Enum & e) {
    return p << static_cast<std::underlying_type_t<Enum>>(e);
}

template <class Enum>
std::enable_if_t<std::is_enum<Enum>::value, sf::Packet &>
operator>>(sf::Packet & p, Enum & e) {
    std::underlying_type_t<Enum> raw;
    p >> raw;
    e = static_cast<Enum>(raw);
    return p;
}

struct Serializer: public boost::static_visitor<> {
    Serializer(sf::Packet & p): p(p) { }

    template <class T>
    void operator()(const T & t) const {
        p << t;
    }

    sf::Packet & p;
};

// template <class... Args>
sf::Packet & operator<<(sf::Packet & p, const network::ServerMessage & var);

template <class T1, class... Tn>
std::enable_if_t<sizeof...(Tn) == 0>
build(int, sf::Packet & p, network::ServerMessage & v) {
    T1 t;
    p >> t;
    v = t;
}

template <class T1, class... Tn>
std::enable_if_t<sizeof...(Tn) != 0>
build(int which, sf::Packet & p, network::ServerMessage & v) {
    if (!which) {
        T1 t;
        p >> t;
        v = t;
    }
    else
        build<Tn...>(which - 1, p, v);
}

// template <class... Args>
sf::Packet & operator>>(sf::Packet & p, network::ServerMessage & var);
