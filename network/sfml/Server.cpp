#include "Server.hpp"

#include "packets.hpp"

#include <unistd.h>

size_t SFMLServer::idCounter { 0 };

SFMLServer::SFMLServer(unsigned width, unsigned height):
    width_  { width },
    height_ { height } {

    server_.setBlocking(false);
}

SFMLServer::~SFMLServer(void) {
    for (const auto & client: clients_) {
        sf::Packet dummy;
        while (client.second->receive(dummy) == sf::Socket::Done)
            ;
        client.second->disconnect();
    }
    clients_.clear();
    server_.close();
}

bool SFMLServer::listen(network::Port port) {
    if (server_.listen(port) == sf::Socket::Done)
        return true;
    return false;
}

void SFMLServer::waitFor(unsigned players) {
    while (players) {
        if (acceptNewConnection())
            --players;
        usleep(10000);
    }
    sleep(1);
}

void SFMLServer::sendMessage(const network::ServerMessage & message) {
    sf::Packet packet;

    packet << message;
    for (const auto & client: clients_)
        client.second->send(packet);
}

network::ClientMessages SFMLServer::getMessages(void) {
    acceptNewConnection(); // Allowing viewers

    std::vector<size_t> leftIds;

    network::ClientMessages messages;
    for (const auto & client: clients_) {
        sf::Packet packet;
        sf::Socket::Status status;
        while ((status = client.second->receive(packet)) == sf::Socket::Done) {
            network::ChangeDirection message;
            message.id = client.first;
            packet >> message.direction;
            messages.push_back(message);
        }
        if (status == sf::Socket::Disconnected) {
            messages.push_back(network::Left { client.first });
            leftIds.push_back(client.first);
        }
    }

    // Removing clients that left
    for (auto id: leftIds)
        clients_.erase(id);

    return messages;
}

bool SFMLServer::acceptNewConnection(void) {
    Client client { new sf::TcpSocket };

    if (server_.accept(*client) == sf::Socket::Done)
    {
        sf::Packet packet;
        packet << width_ << height_;
        client->send(packet);
        client->setBlocking(false);
        clients_.emplace(idCounter++, client);
        return true;
    }
    return false;
}
