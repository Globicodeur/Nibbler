#pragma once

#include <string>

struct GameOptions {
    static int          width, height;
    static bool         torus;
    static unsigned     snakeCount;
    static unsigned     playerCount;
    static std::string  aiFile;

    static void     parseFromCommandLine(int argc, char **argv);
};
