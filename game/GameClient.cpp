#include "GameClient.hpp"

#include "GameOptions.hpp"

#include "spec.hpp"

static const char * NETWORK_LIBRARY = "./nibbler_network_sfml.so";

GameClient::GameClient(void):
    client_ { NETWORK_LIBRARY },
    exited_ { false } {

    using spec::Event;
    using Dispatcher = spec::EventDispatcher;

    Dispatcher::on_<Event::ChangeDirection>(
        [this](size_t, Direction dir) {
            client_->sendDirection(dir);
        }
    );

    Dispatcher::on<Event::Exit>([this] { exited_ = true; });

    client_.init();
    client_->connect(GameOptions::host, GameOptions::port);
}

network::GameState GameClient::getGameState(void) {
    return client_->getGameState();
}

bool GameClient::isRunning(void) {
    return !exited_ && client_->isConnected();
}
