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
        { gui::Input::Up,    [] { Dispatcher::emit<Event::ChangeDirection>(0ul, Up);    } },
        { gui::Input::Down,  [] { Dispatcher::emit<Event::ChangeDirection>(0ul, Down);  } },
        { gui::Input::Left,  [] { Dispatcher::emit<Event::ChangeDirection>(0ul, Left);  } },
        { gui::Input::Right, [] { Dispatcher::emit<Event::ChangeDirection>(0ul, Right); } },
        { gui::Input::W,     [] { Dispatcher::emit<Event::ChangeDirection>(1ul, Up);    } },
        { gui::Input::S,     [] { Dispatcher::emit<Event::ChangeDirection>(1ul, Down);  } },
        { gui::Input::A,     [] { Dispatcher::emit<Event::ChangeDirection>(1ul, Left);  } },
        { gui::Input::D,     [] { Dispatcher::emit<Event::ChangeDirection>(1ul, Right); } },
        { gui::Input::Exit,  Dispatcher::emit<Event::Exit>                                },
        { gui::Input::Key1,  Dispatcher::emit<Event::ChangeGui1>                          },
        { gui::Input::Key2,  Dispatcher::emit<Event::ChangeGui2>                          },
        { gui::Input::Key3,  Dispatcher::emit<Event::ChangeGui3>                          },
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
