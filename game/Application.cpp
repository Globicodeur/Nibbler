#include "Application.hpp"

#include "GameEngine.hpp"
#include "GameOptions.hpp"

#include <unordered_map>

static const char * GRAPHIC_LIBRARY_NAMES[] = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};
constexpr size_t LIBRARY_COUNT = sizeof(GRAPHIC_LIBRARY_NAMES) / sizeof(char *);

static const char * AUDIO_LIBRARY_NAMES[] = {
    "./nibbler_audio_sdl.so",
    "./nibbler_audio_sfml.so",
    "./nibbler_audio_qt.so",
};


Application::Application(int argc, char **argv) {
    GameOptions::parseFromCommandLine(argc, argv);
}

Application::~Application(void) { } // forwarded unique_ptr

void Application::run(void) {
    gui_.load(GRAPHIC_LIBRARY_NAMES, GameOptions::width, GameOptions::height);
    audio_.load(AUDIO_LIBRARY_NAMES);
    size_t i = rand() % LIBRARY_COUNT;
    gui_.swap(i);
    audio_.swap(i);

    auto playAudio = [this](audio::SoundType sound) {
        audio_->play(sound);
    };
    engine_.reset(new GameEngine { playAudio });

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
        { gui::InputType::ChangeGui1, [this] { gui_.swap(0); audio_.swap(0); } },
        { gui::InputType::ChangeGui2, [this] { gui_.swap(1); audio_.swap(1); } },
        { gui::InputType::ChangeGui3, [this] { gui_.swap(2); audio_.swap(2); } },
    };

    auto actionIt = ACTIONS.find(input);
    if (actionIt != ACTIONS.end())
        actionIt->second();
}

void Application::render(void) {
    gui::GameInfo::Snakes snakeBodies;

    for (const auto & snake: engine_->snakes) {
        if (snake.isAlive())
            snakeBodies.push_back(snake.body());
    }

    gui_->draw({ snakeBodies, engine_->food });
}
