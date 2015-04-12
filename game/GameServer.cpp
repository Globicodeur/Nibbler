#include "GameServer.hpp"

#include "GameEngine.hpp"
#include "GameOptions.hpp"

// static const char * NETWORK_LIBRARY = "./nibbler_network_sfml.so";

GameServer::GameServer(void){

    // server_->listen(GameOptions::port);
}

void GameServer::sendGameState(const GameEngine & engine) {
    gui::GameInfo::Snakes snakeBodies;

    for (const auto & snake: engine.snakes()) {
        if (snake.isAlive())
            snakeBodies.push_back(snake.body());
    }

    // server_->sendGameState({ snakeBodies, engine.food() });
}

network::Messages GameServer::getMessages(void) {
    // Mocking for now
    return { network::Message { 0, Right } };
}

