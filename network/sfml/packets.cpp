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

sf::Packet & operator<<(sf::Packet & p, const network::ServerMessage & var) {
    p << var.which();
    boost::apply_visitor(Serializer { p }, var);
    return p;
}

sf::Packet & operator>>(sf::Packet & p, network::ServerMessage & var) {
    int which;
    p >> which;
    build<audio::Sound, gui::GameState>(which, p, var);
    return p;
}
