#include "GameServer.hpp"

#include "GameEngine.hpp"
#include "GameOptions.hpp"

static const char * NETWORK_LIBRARY = "./nibbler_network_sfml.so";

GameServer::GameServer(void):
    server_ { NETWORK_LIBRARY, GameOptions::width, GameOptions::height } {

    server_.init();
    if (!server_->listen(GameOptions::port))
        throw std::system_error { errno, std::system_category() };
}

void GameServer::sendGameState(const GameEngine & engine) {
    gui::GameInfo::Snakes snakeBodies;

    for (const auto & snake: engine.snakes()) {
        if (snake.isAlive())
            snakeBodies.push_back(snake.body());
    }

    server_->sendGameState({ snakeBodies, engine.food() });
}

network::Messages GameServer::getMessages(void) {
    return server_->getMessages();
}

