#pragma once

struct GameOptions {
    static int      width, height;
    static bool     torus;
    static unsigned players;

    static void     parseFromCommandLine(int argc, char **argv);
};
