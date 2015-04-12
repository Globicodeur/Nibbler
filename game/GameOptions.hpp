#pragma once

#include <string>

struct GameOptions {
    using Port          = unsigned short;

    static int          width, height;
    static bool         torus;
    static unsigned     snakeCount;
    static unsigned     playerCount;
    static std::string  aiFile;
    static bool         client;
    static bool         server;
    static std::string  host;
    static Port         port;

    static void         parseFromCommandLine(int argc, char **argv);
};
