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

UserInterface::UserInterface(void) {
    using spec::Event;
    using Dispatcher = spec::EventDispatcher;

    auto swapInterface = [this](auto i) {
        graphics_.swap(i), audio_.swap(i);
    };

    Dispatcher::on<Event::ChangeGui, size_t>(swapInterface);
    Dispatcher::on_<Event::PlaySound>(
        [this](audio::Sound sound) { audio_->play(sound); }
    );

    graphics_.load(
        GRAPHIC_LIBRARY_NAMES,
        GameOptions::width,
        GameOptions::height
    );
    audio_.load(AUDIO_LIBRARY_NAMES);

    swapInterface(rand() % LIBRARY_COUNT);
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

    render({ snakeBodies, engine.food() });
}

void UserInterface::render(const gui::GameInfo & info) {
    graphics_->draw(info);
}
