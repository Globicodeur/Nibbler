#pragma once

#include "tools/SharedObject.hpp"

#include "network/spec.hpp"

class GameClient {

public:
                        GameClient(void);

    // 42 norme
                        ~GameClient(void)               = default;
                        GameClient(const GameClient &)  = delete;
    GameClient &        operator=(const GameClient &)   = delete;
    //

    network::GameState  getGameState(void);
    bool                isRunning(void);

private:
    using Client        = SharedObject<network::Client>;

    Client              client_;
    bool                exited_;
};
