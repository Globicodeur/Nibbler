#include "Client.hpp"

#include "packets.hpp"

SFMLClient::SFMLClient(void):
    connected_ { false } {
}

SFMLClient::~SFMLClient(void) {
    socket_.disconnect();
}

bool SFMLClient::connect(const std::string & host, network::Port port) {
    if (socket_.connect(sf::IpAddress { host }, port) == sf::Socket::Done) {
        connected_ = true;
        return true;
    }
    return false;
}

network::ServerMessages SFMLClient::getMessages(void) {
    network::ServerMessages messages;
    sf::Packet packet;

    auto status = socket_.receive(packet);
    if (status == sf::Socket::Done) {
        network::ServerMessage message;
        packet >> message;
        messages.push_back(message);
    }
    else if (status != sf::Socket::NotReady)
        connected_ = false;
    return messages;
}

SFMLClient::Dimensions SFMLClient::getDimensions(void) {
    sf::Packet packet;
    if (socket_.receive(packet) == sf::Socket::Done)
    {
        socket_.setBlocking(false);
        unsigned width, height;
        packet >> width;
        packet >> height;
        return { width, height };
    }
    return { 10, 10 };
}

void SFMLClient::sendDirection(Direction direction) {
    sf::Packet packet;
    packet << direction;
    socket_.send(packet);
}

bool SFMLClient::isConnected(void) {
    return connected_;
}
