#pragma once

#include "tools/SharedObject.hpp"

#include "network/spec.hpp"

class GameClient {

public:
                            GameClient(void);

    network::ServerMessages getMessages(void);
    bool                    isRunning(void);

private:
    using Client            = SharedObject<network::Client>;

    Client                  client_;
    bool                    exited_;
};
