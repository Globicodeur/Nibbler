#include "Application.hpp"

#include "GameOptions.hpp"

#include "GameEngine.hpp"
#include "GameServer.hpp"
#include "GameClient.hpp"

#include "UserInterface.hpp"

#include "dispatch.hpp"

Application::Application(int argc, char **argv) {
    GameOptions::parseFromCommandLine(argc, argv);
}

void Application::run(void) {
    if (GameOptions::server)
        runServer();
    else if (GameOptions::client)
        runClient();
    else
        runLocal();
}

void Application::runLocal(void) {
    GameEngine engine;
    UserInterface interface;

    while (engine.isRunning()) {
        for (auto input: interface.getInputs())
            spec::dispatchInput(input);

        engine.update();
    }
}

void Application::runClient(void) {
    GameClient client;
    UserInterface interface;

    while (client.isRunning()) {
        for (auto input: interface.getInputs())
            spec::dispatchInput(input);

        for (const auto & message: client.getMessages())
            spec::dispatchMessage(message);
    }
}

void Application::runServer(void) {
    GameEngine engine;
    GameServer server;

    while (engine.isRunning()) {
        for (auto message: server.getMessages())
            spec::dispatchMessage(message);

        engine.update();
    }
}
