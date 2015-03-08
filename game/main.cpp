#include "nibbler.hpp"
#include "GameEngine.hpp"
#include "Snake.hpp"

typedef void (*init_t)();
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
    Snake           *snake = game.snake;
    gui::InputType  input;
    gui::GameInfo   gameInfo;

    handle = dlopen("nibbler_gui_sfml.so", RTLD_LAZY);
    if (!handle) {
        fputs(dlerror(), stderr);
        exit(1);
    }

    init = dlsymSafe<init_t>(handle, "init");
    clean = dlsymSafe<clean_t>(handle, "clean");
    draw = dlsymSafe<draw_t>(handle, "draw");
    getInput = dlsymSafe<getInput_t>(handle, "getInput");

    gameInfo.width = game.width;
    gameInfo.height = game.height;
    gameInfo.snake = game.snake->body;
    gameInfo.food = game.food;

    (*init)();
    while (game.running)
    {
        input = (*getInput)();
        switch (input) {
            case gui::InputType::Up:
                snake->direction = UP;
                break ;
            case gui::InputType::Down:
                snake->direction = DOWN;
                break ;
            case gui::InputType::Left:
                snake->direction = LEFT;
                break ;
            case gui::InputType::Right:
                snake->direction = RIGHT;
                break ;
            case gui::InputType::Exit:
            default:
                break ;
        }
        if (!snake->move(game))
            break ;
        (*draw)(gameInfo);
    }

    (*clean)();
    dlclose(handle);
}

int         main(void) {
    GameEngine  game(30, 30);

    srand(time(0));
    game.spawnFood();
    gameLoop(game);
}
