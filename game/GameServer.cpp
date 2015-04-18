#include "GameServer.hpp"

#include "GameOptions.hpp"

#include "spec.hpp"

static const char * NETWORK_LIBRARY = "./nibbler_network_sfml.so";

GameServer::GameServer(void):
    server_ { NETWORK_LIBRARY, GameOptions::width, GameOptions::height } {

    using spec::Event;
    using Dispatcher = spec::EventDispatcher;

    Dispatcher::on_<Event::PlaySound>([this](audio::Sound sound) {
        server_->sendMessage(sound);
    });
    Dispatcher::on_<Event::Draw>([this](const gui::GameState & info) {
        server_->sendMessage(info);
    });

    server_.init();

    if (!server_->listen(GameOptions::port))
        throw std::system_error { errno, std::system_category() };
}

network::ClientMessages GameServer::getMessages(void) {
    return server_->getMessages();
}

