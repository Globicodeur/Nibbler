#pragma once

#include "tools/SharedObject.hpp"

#include "network/spec.hpp"

class GameServer {

public:
                            GameServer(void);

    // 42 norme
                            ~GameServer(void)               = default;
                            GameServer(const GameServer &)  = delete;
    GameServer &            operator=(const GameServer &)   = delete;
    //

    network::ClientMessages getMessages(void);

private:
    using Server            = SharedObject<network::Server>;

    Server                  server_;
};
