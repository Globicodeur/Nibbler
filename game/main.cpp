#include "tools/Timer.hpp"
#include "GameEngine.hpp"
#include "GuiManager.hpp"

#include "command_line.hpp"

int main(int argc, char **argv) {
    parseCommandLine(argc, argv);

    using StepTimer = Timer<std::chrono::milliseconds>;

    GameEngine      game;
    GuiManager      guiManager;
    StepTimer       stepTimer;

    if (!guiManager.isValid())
        return -1;

    while (game.running)
    {
        for (auto input: guiManager.getInputs()) {
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
        }

        if (stepTimer.elapsed() >= 100) {
            game.update();
            stepTimer.reset();
        }

        guiManager.draw(game);
    }

    return 0;
}
