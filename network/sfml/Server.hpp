#pragma once

#include <SFML/network.hpp>
#include <unordered_map>

#include "spec.hpp"

class SFMLServer: public network::Server {

public:
                                    SFMLServer(unsigned, unsigned);
    virtual                         ~SFMLServer(void);

    // 42 norme
                                    SFMLServer(void) = delete;
                                    SFMLServer(const SFMLServer &) = delete;
    SFMLServer &                    operator=(const SFMLServer &) = delete;
    //

    virtual bool                    listen(network::Port port);
    virtual void                    waitFor(unsigned players);
    virtual void                    sendMessage(const network::ServerMessage &);
    virtual network::ClientMessages getMessages(void);

private:
    using Client                    = std::shared_ptr<sf::TcpSocket>;
    using Clients                   = std::unordered_map<size_t, Client>;

    sf::TcpListener                 server_;
    Clients                         clients_;

    static size_t                   idCounter;

    unsigned                        width_, height_;

    bool                            acceptNewConnection(void);
};
