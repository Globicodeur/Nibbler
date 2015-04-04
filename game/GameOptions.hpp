#pragma once

struct GameOptions {
    static int      width, height;
    static bool     torus;
    static unsigned snakeCount;
    static unsigned playerCount;

    static void     parseFromCommandLine(int argc, char **argv);
};
