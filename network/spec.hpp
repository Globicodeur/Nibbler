#pragma once

#include <vector>

#include "../gui/spec.hpp"
#include "../Tools/Direction.hpp"

namespace network {

    using gui::GameInfo;

    struct Message {
        size_t id;
        Direction direction;
    };

    using Messages = std::vector<Message>;

    using Port = unsigned short;

    struct Server {

        struct SharedObjectInfo {
            using Getter = Server * (*)(void);
            static constexpr const char * getterName() { return "getServer"; }
        };

        virtual bool        listen(Port port)                       = 0;
        virtual void        sendGameState(const GameInfo & info)    = 0;
        virtual Messages    getMessages(void)                       = 0;

    };

    using GameState = std::shared_ptr<GameInfo>;

    struct Client {

        struct SharedObjectInfo {
            using Getter = Client * (*)(void);
            static constexpr const char * getterName() { return "getClient"; }
        };

        virtual bool        connect(const std::string & host, Port port)    = 0;
        virtual GameState   getGameState(void)                              = 0;
        virtual void        sendDirection(Direction direction)              = 0;
        virtual bool        isConnected(void)                               = 0;

    };

}
