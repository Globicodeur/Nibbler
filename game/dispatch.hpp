#pragma once

#include "spec.hpp"
#include "gui/spec.hpp"
#include "network/spec.hpp"

namespace spec {

    void dispatchInput(gui::Input);
    void dispatchMessage(const network::ClientMessage &);
    void dispatchMessage(const network::ServerMessage &);

}
