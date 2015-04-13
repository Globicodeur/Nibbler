#include "Application.hpp"

#include "GameOptions.hpp"

#include "GameEngine.hpp"
#include "GameServer.hpp"
#include "GameClient.hpp"

#include "UserInterface.hpp"

#include "spec.hpp"
#include "gui/spec.hpp"
#include "network/spec.hpp"

#include <unordered_map>

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

static void dispatchInput(gui::Input);

void Application::runLocal(void) {
    GameEngine engine;
    UserInterface interface;

    while (engine.isRunning()) {
        for (auto input: interface.getInputs())
            dispatchInput(input);

        if (engine.update())
            interface.render(engine);
    }
}

void Application::runClient(void) {
    GameClient client;
    UserInterface interface;

    while (client.isRunning()) {
        for (auto input: interface.getInputs())
            dispatchInput(input);

        auto state = client.getGameState();
        if (state)
            interface.render(*state);
    }
}

static void dispatchMessage(const network::Message &);

void Application::runServer(void) {
    GameEngine engine;
    GameServer server;

    while (engine.isRunning()) {
        for (auto message: server.getMessages())
            dispatchMessage(message);

        if (engine.update())
            server.sendGameState(engine);
    }
}

using spec::Event;
using Dispatcher = spec::EventDispatcher;

template <Event event, class...Args>
static auto lazyDispatch(Args... args) {
    return [=] { Dispatcher::emit<event>(args...); };
}

static void dispatchInput(gui::Input input) {
    using Emitter = std::function<void ()>;
    using DispatchMap = std::unordered_map<gui::Input, Emitter>;

    static const DispatchMap DISPATCHERS = {
        { gui::Input::Up,    lazyDispatch<Event::ChangeDirection>(0ul, Up)    },
        { gui::Input::Down,  lazyDispatch<Event::ChangeDirection>(0ul, Down)  },
        { gui::Input::Left,  lazyDispatch<Event::ChangeDirection>(0ul, Left)  },
        { gui::Input::Right, lazyDispatch<Event::ChangeDirection>(0ul, Right) },
        { gui::Input::W,     lazyDispatch<Event::ChangeDirection>(1ul, Up)    },
        { gui::Input::S,     lazyDispatch<Event::ChangeDirection>(1ul, Down)  },
        { gui::Input::A,     lazyDispatch<Event::ChangeDirection>(1ul, Left)  },
        { gui::Input::D,     lazyDispatch<Event::ChangeDirection>(1ul, Right) },
        { gui::Input::Key1,  lazyDispatch<Event::ChangeGui>(0ul)              },
        { gui::Input::Key2,  lazyDispatch<Event::ChangeGui>(1ul)              },
        { gui::Input::Key3,  lazyDispatch<Event::ChangeGui>(2ul)              },
        { gui::Input::Exit,  Dispatcher::emit<Event::Exit>                    },
    };

    auto actionIt = DISPATCHERS.find(input);
    if (actionIt != DISPATCHERS.end())
        actionIt->second();
}

static void dispatchMessage(const network::Message & message) {
    Dispatcher::emit<Event::ChangeDirection>(message.id, message.direction);
}
