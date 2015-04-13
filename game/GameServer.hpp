#pragma once

#include "tools/SharedObject.hpp"

#include "network/spec.hpp"

class GameEngine;

class GameServer {

public:
                        GameServer(void);

    // 42 norme
                        ~GameServer(void)               = default;
                        GameServer(const GameServer &)  = delete;
    GameServer &        operator=(const GameServer &)   = delete;
    //

    void                sendGameState(const GameEngine &);
    network::Messages   getMessages(void);

private:
    using Server        = SharedObject<network::Server>;

    Server              server_;
};
