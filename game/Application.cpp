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

        render();
    }
}

void Application::handleInput(gui::InputType input) {
    using Action = std::function<void ()>;
    using ActionMap = std::unordered_map<gui::InputType, Action>;

    static const ActionMap ACTIONS = {
        { gui::InputType::Up,         [this] { engine_->turnSnake(0, Up);    } },
        { gui::InputType::Down,       [this] { engine_->turnSnake(0, Down);  } },
        { gui::InputType::Left,       [this] { engine_->turnSnake(0, Left);  } },
        { gui::InputType::Right,      [this] { engine_->turnSnake(0, Right); } },
        { gui::InputType::W,          [this] { engine_->turnSnake(1, Up);    } },
        { gui::InputType::S,          [this] { engine_->turnSnake(1, Down);  } },
        { gui::InputType::A,          [this] { engine_->turnSnake(1, Left);  } },
        { gui::InputType::D,          [this] { engine_->turnSnake(1, Right); } },
        { gui::InputType::Exit,       [this] { engine_->running = false;     } },
        { gui::InputType::ChangeGui1, [this] { gui_.swap(0);                 } },
        { gui::InputType::ChangeGui2, [this] { gui_.swap(1);                 } },
        { gui::InputType::ChangeGui3, [this] { gui_.swap(2);                 } },
    };

    auto actionIt = ACTIONS.find(input);
    if (actionIt != ACTIONS.end())
        actionIt->second();
}

void Application::render() {
    gui::GameInfo::Snakes snakeBodies;

    for (const auto & snake: engine_->snakes) {
        if (snake.isAlive())
            snakeBodies.push_back(snake.body());
    }

    gui_->draw({ snakeBodies, engine_->food });
}
