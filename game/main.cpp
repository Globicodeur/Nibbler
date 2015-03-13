#include "Timer.hpp"
#include "GameEngine.hpp"
#include "Snake.hpp"
#include "GuiManager.hpp"

static const GuiManager::LibraryNames LIBRARIES = {
    "nibbler_gui_sfml.so"
};

static void gameLoop(GameEngine &game) {
    using StepTimer = Timer<std::chrono::milliseconds>;

    StepTimer       stepTimer;
    gui::InputType  input;
    GuiManager      guiManager { game.width, game.height, LIBRARIES };

    bool loadOk = guiManager.changeLibrary(rand() % LIBRARIES.size());
    if (!loadOk)
        return ;

    while (game.running)
    {
        input = guiManager.getInput();
        switch (input) {
            case gui::InputType::Up:
                game.snake->changeDirection(UP);
                break ;
            case gui::InputType::Down:
                game.snake->changeDirection(DOWN);
                break ;
            case gui::InputType::Left:
                game.snake->changeDirection(LEFT);
                break ;
            case gui::InputType::Right:
                game.snake->changeDirection(RIGHT);
                break ;
            case gui::InputType::Exit:
                game.running = false;
                break ;
            case gui::InputType::ChangeGui1:
            case gui::InputType::ChangeGui2:
            case gui::InputType::ChangeGui3:
                if (!guiManager.changeLibrary(
                    static_cast<int>(input) -
                    static_cast<int>(gui::InputType::ChangeGui1)
                ))
                    return ;
                break;
            default:
                break ;
        }

        if (stepTimer.elapsed() >= 20) {
            game.update();
            stepTimer.reset();
        }

        guiManager.draw(game);
    }
}

int         main(void) {
    GameEngine  game(18, 32);

    srand(time(0));
    gameLoop(game);
}
