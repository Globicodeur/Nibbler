#pragma once

#include "tools/SharedObject.hpp"

#include "network/spec.hpp"

class GameServer {

public:
                            GameServer(void);

    network::ClientMessages getMessages(void);

private:
    using Server            = SharedObject<network::Server>;

    Server                  server_;
};
