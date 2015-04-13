#include "Server.hpp"

#include "packets.hpp"

size_t SFMLServer::idCounter { 0 };

SFMLServer::SFMLServer(void) {
    server_.setBlocking(false);
}

SFMLServer::~SFMLServer(void) {
    for (const auto & client: clients_)
        client.second->disconnect();
    server_.close();
}

bool SFMLServer::listen(network::Port port) {
    server_.listen(port);
    return true;
}

void SFMLServer::sendGameState(const network::GameInfo & info) {
    sf::Packet p;
    p << info;
    for (const auto & client: clients_)
        client.second->send(p);
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
        client->setBlocking(false);
        // std::cout << client->getRemoteAddress() << std::endl;
        clients_.emplace(idCounter++, client);
    }
}
