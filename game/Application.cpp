#include "Application.hpp"

#include "GameEngine.hpp"
#include "GameOptions.hpp"

#include "UserInterface.hpp"

#include "gui/spec.hpp"
#include "spec.hpp"

#include <unordered_map>

Application::Application(int argc, char **argv) {
    GameOptions::parseFromCommandLine(argc, argv);
}

Application::~Application(void) { } // forwarded unique_ptr

void Application::run(void) {
    runLocal();
}

static void dispatchInput(gui::Input input) {
    using spec::Event;
    using Dispatcher = spec::EventDispatcher;
    using Emitter = std::function<void ()>;
    using DispatchMap = std::unordered_map<gui::Input, Emitter>;

    static const DispatchMap DISPATCH = {
        { gui::Input::Up,    Dispatcher::emit<Event::UpP1>       },
        { gui::Input::Down,  Dispatcher::emit<Event::DownP1>     },
        { gui::Input::Left,  Dispatcher::emit<Event::LeftP1>     },
        { gui::Input::Right, Dispatcher::emit<Event::RightP1>    },
        { gui::Input::W,     Dispatcher::emit<Event::UpP2>       },
        { gui::Input::S,     Dispatcher::emit<Event::DownP2>     },
        { gui::Input::A,     Dispatcher::emit<Event::LeftP2>     },
        { gui::Input::D,     Dispatcher::emit<Event::RightP2>    },
        { gui::Input::Exit,  Dispatcher::emit<Event::Exit>       },
        { gui::Input::Key1,  Dispatcher::emit<Event::ChangeGui1> },
        { gui::Input::Key2,  Dispatcher::emit<Event::ChangeGui2> },
        { gui::Input::Key3,  Dispatcher::emit<Event::ChangeGui3> },
    };

    auto actionIt = DISPATCH.find(input);
    if (actionIt != DISPATCH.end())
        actionIt->second();
}

void Application::runLocal(void) {
    GameEngine engine;
    UserInterface interface;

    while (engine.isRunning()) {
        for (auto input: interface.getInputs())
            dispatchInput(input);

        engine.update();

        interface.render(engine);
    }
}
