#include "Server.hpp"

#include "packets.hpp"

size_t SFMLServer::idCounter { 0 };

SFMLServer::SFMLServer(unsigned width, unsigned height):
    width_  { width },
    height_ { height } {

    server_.setBlocking(false);
}

SFMLServer::~SFMLServer(void) {
    server_.close();
    for (const auto & client: clients_) {
        sf::Packet dummy;
        while (client.second->receive(dummy) == sf::Socket::Done)
            ;
        client.second->disconnect();
    }
    clients_.clear();
}

bool SFMLServer::listen(network::Port port) {
    if (server_.listen(port) == sf::Socket::Done)
        return true;
    return false;
}

void SFMLServer::sendGameState(const network::GameInfo & info) {
    sf::Packet packet;

    packet << info;
    for (const auto & client: clients_)
        client.second->send(packet);
}

network::Messages SFMLServer::getMessages(void) {
    acceptNewConnection();

    network::Messages messages;
    for (const auto & client: clients_) {
        sf::Packet packet;
        while (client.second->receive(packet) == sf::Socket::Done) {
            network::Message message;
            message.id = client.first;
            packet >> message.direction;
            messages.push_back(message);
        }
    }
    return messages;
}

void SFMLServer::acceptNewConnection(void) {
    Client client { new sf::TcpSocket };

    if (server_.accept(*client) == sf::Socket::Done)
    {
        sf::Packet packet;
        packet << width_ << height_;
        client->send(packet);
        client->setBlocking(false);
        clients_.emplace(idCounter++, client);
    }
}