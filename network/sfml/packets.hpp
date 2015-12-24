#pragma once

#include <SFML/Network.hpp>

#include <boost/mpl/size.hpp>

#include "spec.hpp"

sf::Packet & operator<<(sf::Packet & p, const Position & pos);
sf::Packet & operator>>(sf::Packet & p, Position & pos);
sf::Packet & operator<<(sf::Packet & p, const gui::GameState & info);
sf::Packet & operator>>(sf::Packet & p, gui::GameState & info);
sf::Packet & operator<<(sf::Packet & p, const gui::GameState::Snake & snake);
sf::Packet & operator>>(sf::Packet & p, gui::GameState::Snake & snake);

// Vectors
template <class T>
sf::Packet & operator>>(sf::Packet & p, std::vector<T> & v) {
    sf::Uint32 size;
    p >> size;
    v.resize(size);
    for (sf::Uint32 i = 0; i < size; ++i)
        p >> v[i];
    return p;
}

template <class T>
sf::Packet & operator<<(sf::Packet & p, const std::vector<T> & v) {
    p << static_cast<sf::Uint32>(v.size());
    for (const auto & t: v)
        p << t;
    return p;
}

// Enums
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

// Variants
template <class Stream>
struct VariantSerializer: boost::static_visitor<> {

    VariantSerializer(Stream & stream):
        stream_ { stream }
    { }

    template <class T>
    void operator()(const T & t) const {
        stream_ << t;
    }

private:
    Stream & stream_;
};

template <class... Args>
sf::Packet & operator<<(sf::Packet & p, const boost::variant<Args...> & var) {
    p << var.which();
    boost::apply_visitor(VariantSerializer<sf::Packet> { p }, var);
    return p;
}

template <class T, class Var>
static void load(sf::Packet & p, Var & v) {
    T t;
    p >> t;
    v = t;
}

template <size_t limit, class Var, class T1, class... Tn>
std::enable_if_t<limit == 0>
load(int, sf::Packet & p, Var & v) {
    load<T1>(p, v);
}

template <size_t limit, class Var, class T1, class... Tn>
std::enable_if_t<limit != 0>
load(int which, sf::Packet & p, Var & v) {
    if (!which)
        load<T1>(p, v);
    else
        load<limit - 1, Var, Tn...>(which - 1, p, v);
}

template <class... Args>
sf::Packet & operator>>(sf::Packet & p, boost::variant<Args...> & var) {
    using VarT = boost::variant<Args...>;
    using types = typename VarT::types;
    static constexpr auto size = boost::mpl::size<types>::value;

    int which;
    p >> which;
    load<size - 1, VarT, Args...>(which, p, var);
    return p;
}
