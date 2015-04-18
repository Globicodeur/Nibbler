#include "GameClient.hpp"

#include "GameOptions.hpp"

#include "spec.hpp"

#include <iostream>

static const char * NETWORK_LIBRARY = "./nibbler_network_sfml.so";

GameClient::GameClient(void):
    client_ { NETWORK_LIBRARY },
    exited_ { false } {

    using spec::Event;
    using Dispatcher = spec::EventDispatcher;

    Dispatcher::on_<Event::ChangeDirection>([this](size_t, Direction dir) {
        client_->sendDirection(dir);
    });
    Dispatcher::on<Event::Exit>([this] { exited_ = true; });

    client_.init();

    if (!client_->connect(GameOptions::host, GameOptions::port)) {
        std::cerr << "Error connecting to "
                  << GameOptions::host << ":" << GameOptions::port
                  << std::endl;
        throw std::system_error { errno, std::system_category() };
    }

    std::tie(GameOptions::width, GameOptions::height) = client_->getDimensions();
}

network::ServerMessages GameClient::getMessages(void) {
    return client_->getMessages();
}

bool GameClient::isRunning(void) {
    return !exited_ && client_->isConnected();
}
