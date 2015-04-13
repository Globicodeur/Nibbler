#include "Client.hpp"

#include "packets.hpp"

SFMLClient::SFMLClient(void):
    connected_ { false } {
    socket_.setBlocking(false);
}

SFMLClient::~SFMLClient(void) {
    socket_.disconnect();
}

bool SFMLClient::connect(const std::string & host, network::Port port) {
    socket_.connect(sf::IpAddress { host }, port);
    connected_ = true;
    return true;
}

network::GameState SFMLClient::getGameState(void) {
    network::GameState state;

    sf::Packet p;
    auto status = socket_.receive(p);
    if (status == sf::Socket::Done) {
        state.reset(new network::GameInfo);
        p >> *state;
    }
    else if (status != sf::Socket::NotReady)
        connected_ = false;
    return state;
}

void SFMLClient::sendDirection(Direction direction) {
    sf::Packet p;
    p << direction;
    socket_.send(p);
}

bool SFMLClient::isConnected(void) {
    return connected_;
}
