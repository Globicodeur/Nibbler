#include "nibbler.hpp"
#include "GameEngine.hpp"
#include "Snake.hpp"
#include "Timer.hpp"

typedef void (*init_t)(uint, uint);
typedef void (*clean_t)();
typedef void (*draw_t)(const gui::GameInfo &);
typedef gui::InputType (*getInput_t)();

template<class T>
static T    dlsymSafe(void *handle, const char *toGet) {
    T       symbol;
    char    *error;

    symbol = reinterpret_cast<T>(dlsym(handle, toGet));
    if ((error = dlerror()) != nullptr)  {
        std::cerr << error << std::endl;
        return nullptr;
    }
    return symbol;
}

static void gameLoop(GameEngine &game) {
    void            *handle;
    init_t          init;
    clean_t         clean;
    draw_t          draw;
    getInput_t      getInput;
    Snake           *snake = game.snake.get();
    gui::InputType  input;

    handle = dlopen("nibbler_gui_sfml.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    init = dlsymSafe<init_t>(handle, "init");
    clean = dlsymSafe<clean_t>(handle, "clean");
    draw = dlsymSafe<draw_t>(handle, "draw");
    getInput = dlsymSafe<getInput_t>(handle, "getInput");

    if (!init || !clean || !draw || !getInput)
        return ;


    Timer<std::chrono::milliseconds> stepTimer;
    (*init)(game.width, game.height);
    while (game.running)
    {
        input = (*getInput)();
        switch (input) {
            case gui::InputType::Up:
                snake->changeDirection(UP);
                break ;
            case gui::InputType::Down:
                snake->changeDirection(DOWN);
                break ;
            case gui::InputType::Left:
                snake->changeDirection(LEFT);
                break ;
            case gui::InputType::Right:
                snake->changeDirection(RIGHT);
                break ;
            case gui::InputType::Exit:
                game.running = false;
                break ;
            default:
                break ;
        }
        if (stepTimer.elapsed() >= 100) {
            game.update();
            stepTimer.reset();
        }
        gui::GameInfo   gameInfo;
        std::transform(
            game.snake->body().begin(),
            game.snake->body().end(),
            std::back_inserter(gameInfo.snake),
            [](const Position & pos) -> gui::GameInfo::position {
                return { pos.x, pos.y };
            }
        );
        gameInfo.food = { game.food.x, game.food.y };
        (*draw)(gameInfo);
    }

    (*clean)();
    dlclose(handle);
}

int         main(void) {
    GameEngine  game(18, 32);

    srand(time(0));
    gameLoop(game);
}
