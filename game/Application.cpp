#include "Application.hpp"

#include "GameEngine.hpp"
#include "command_line.hpp"

#include <unordered_map>

static const char * GRAPHIC_LIBRARY_NAMES[] = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};

Application::Application(int argc, char **argv) {
    parseCommandLine(argc, argv);
}

Application::~Application(void) {

}

void Application::run(void) {
    engine_.reset(new GameEngine);
    gui_.load(
        GRAPHIC_LIBRARY_NAMES,
        GameEngine::width,
        GameEngine::height
    );

    while (engine_->running) {
        for (auto input: gui_->getInputs())
            handleInput(input);
        engine_->update();

        gui_->draw({
            engine_->snake.body(),
            engine_->food
        });
    }
}

void Application::handleInput(gui::InputType input) {
    using Action = std::function<void ()>;
    using ActionMap = std::unordered_map<gui::InputType, Action>;

    static const ActionMap ACTIONS = {
        { gui::InputType::Up,         [this] { engine_->snake.turn(Up);    } },
        { gui::InputType::Down,       [this] { engine_->snake.turn(Down);  } },
        { gui::InputType::Left,       [this] { engine_->snake.turn(Left);  } },
        { gui::InputType::Right,      [this] { engine_->snake.turn(Right); } },
        { gui::InputType::Exit,       [this] { engine_->running = false;   } },
        { gui::InputType::ChangeGui1, [this] { gui_.swap(0);               } },
        { gui::InputType::ChangeGui2, [this] { gui_.swap(1);               } },
        { gui::InputType::ChangeGui3, [this] { gui_.swap(2);               } },
    };

    auto actionIt = ACTIONS.find(input);
    if (actionIt != ACTIONS.end())
        actionIt->second();
}
