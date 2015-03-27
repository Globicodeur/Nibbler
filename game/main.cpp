#include "Timer.hpp"
#include "GameEngine.hpp"
#include "Snake.hpp"
#include "GuiManager.hpp"

static const GuiManager::LibraryNames LIBRARIES = {
    "./nibbler_gui_sdl.so",
    "./nibbler_gui_sfml.so",
    "./nibbler_gui_qt.so",
};

static void gameLoop(GameEngine &game) {
    using StepTimer = Timer<std::chrono::milliseconds>;

    StepTimer       stepTimer;
    gui::InputType  input;
    GuiManager      guiManager { 32, 18, LIBRARIES };

    bool loadOk = guiManager.changeLibrary(rand() % LIBRARIES.size());
    if (!loadOk)
        return ;

    while (game.running)
    {
        input = guiManager.getInput();
        switch (input) {
            case gui::InputType::Up:
            case gui::InputType::Down:
            case gui::InputType::Left:
            case gui::InputType::Right:
                game.snake->changeDirection(static_cast<Direction>(input));
                break ;
            case gui::InputType::Exit:
                game.running = false;
                break ;
            case gui::InputType::ChangeGui1:
            case gui::InputType::ChangeGui2:
            case gui::InputType::ChangeGui3:
                if (!guiManager.changeLibrary(input - gui::ChangeGui1))
                    return ;
                break;
            default:
                break ;
        }

        if (stepTimer.elapsed() >= 100) {
            game.update();
            stepTimer.reset();
        }

        guiManager.draw(game);
    }
}

int         main(void) {
    // Randomization
    srand(time(nullptr));

    GameEngine  game(32, 18);

    gameLoop(game);
}
