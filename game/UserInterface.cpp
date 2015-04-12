#include "UserInterface.hpp"

#include "GameOptions.hpp"
#include "GameEngine.hpp"

#include "spec.hpp"

static const char * GRAPHIC_LIBRARY_NAMES[] = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};

static const char * AUDIO_LIBRARY_NAMES[] = {
    "./nibbler_audio_sdl.so",
    "./nibbler_audio_sfml.so",
    "./nibbler_audio_qt.so",
};

constexpr auto LIBRARY_COUNT = sizeof(GRAPHIC_LIBRARY_NAMES) / sizeof(char *);

using spec::Event;
using Dispatcher = spec::EventDispatcher;

UserInterface::UserInterface(void) {
    auto swap = [this](auto i) { graphics_.swap(i), audio_.swap(i); };
    Dispatcher::on<Event::ChangeGui1>(std::bind(swap, 0));
    Dispatcher::on<Event::ChangeGui2>(std::bind(swap, 1));
    Dispatcher::on<Event::ChangeGui3>(std::bind(swap, 2));
    Dispatcher::on<Event::PlaySound, audio::Sound>(
        [this](auto sound) { audio_->play(sound); }
    );

    graphics_.load(
        GRAPHIC_LIBRARY_NAMES,
        GameOptions::width,
        GameOptions::height
    );
    audio_.load(AUDIO_LIBRARY_NAMES);

    swap(rand() % LIBRARY_COUNT);
}

gui::Inputs UserInterface::getInputs(void) {
    return graphics_->getInputs();
}

void UserInterface::render(const GameEngine & engine) {
    gui::GameInfo::Snakes snakeBodies;

    for (const auto & snake: engine.snakes()) {
        if (snake.isAlive())
            snakeBodies.push_back(snake.body());
    }

    graphics_->draw({ snakeBodies, engine.food() });
}
