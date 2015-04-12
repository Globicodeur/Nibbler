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

    struct Server {

        using Port      = unsigned short;

        struct SharedObjectInfo {
            using Getter = Server * (*)(void);
            static constexpr const char * getterName() { return "getServer"; }
        };

        virtual bool        listen(Port port)                       = 0;
        virtual void        sendGameState(const GameInfo & info)    = 0;
        virtual Messages    getMessages(void)                       = 0;

    };

    struct Client {

        struct SharedObjectInfo {
            using Getter = Client * (*)(void);
            static constexpr const char * getterName() { return "getClient"; }
        };

    };

}
