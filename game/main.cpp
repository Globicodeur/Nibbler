#include <cstdlib>

#include "Timer.hpp"
#include "GameEngine.hpp"
#include "GuiManager.hpp"

int         main(void) {
    srand(time(nullptr));

    using StepTimer = Timer<std::chrono::milliseconds>;

    GameEngine      game { 32, 18 };
    GuiManager      guiManager { 32, 18 };
    StepTimer       stepTimer;
    gui::InputType  input;

    if (!guiManager.isValid())
        return -1;

    while (game.running)
    {
        input = guiManager.getInput();
        switch (input) {
            case gui::InputType::Up:
            case gui::InputType::Down:
            case gui::InputType::Left:
            case gui::InputType::Right:
                game.snake.changeDirection(static_cast<Direction>(input));
                break ;
            case gui::InputType::Exit:
                game.running = false;
                break ;
            case gui::InputType::ChangeGui1:
            case gui::InputType::ChangeGui2:
            case gui::InputType::ChangeGui3:
                guiManager.changeLibrary(input - gui::ChangeGui1);
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

    return 0;
}
