#pragma once

#include <SFML/Network.hpp>

#include "spec.hpp"

class SFMLClient: public network::Client {

public:
                                    SFMLClient(void);
    virtual                         ~SFMLClient(void);

    virtual bool                    connect(const std::string & host, network::Port port);
    virtual Dimensions              getDimensions(void);
    virtual network::ServerMessages getMessages(void);
    virtual void                    sendDirection(Direction direction);
    virtual bool                    isConnected(void);

private:
    sf::TcpSocket                   socket_;
    bool                            connected_;
};
