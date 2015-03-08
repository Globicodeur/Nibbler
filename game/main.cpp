#include "nibbler.hpp"
#include "GameEngine.hpp"
#include "Snake.hpp"

typedef void (*init_t)(uint, uint);
typedef void (*clean_t)();
typedef void (*draw_t)(gui::GameInfo &);
typedef gui::InputType (*getInput_t)();

template<class T>
static T    dlsymSafe(void *handle, const char *toGet) {
    T       symbol;
    char    *error;

    symbol = (T)dlsym(handle, toGet);
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
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
        usleep(500000);
        game.update();
        std::cout << game.snake->body().size() << std::endl;
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
    GameEngine  game(30, 30);

    srand(time(0));
    gameLoop(game);
}
