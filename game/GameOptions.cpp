#include "GameOptions.hpp"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int                 GameOptions::width          { 32 };
int                 GameOptions::height         { 18 };
bool                GameOptions::torus          { false };
unsigned            GameOptions::snakeCount     { 1 };
unsigned            GameOptions::playerCount    { 1 };
std::string         GameOptions::aiFile         { "ai/idle.py" };
bool                GameOptions::client         { false };
bool                GameOptions::server         { false };
std::string         GameOptions::host           { "localhost" };
GameOptions::Port   GameOptions::port           { 1337 };

template <class T>
static auto validateRange(T minBound, T maxBound, const char * description) {
    return [=](const T & value) {

        const auto error = [=](const char * msg) {
            std::cerr << "The value for " << description << " " << msg << ": "
                      << value << " (must be between " << minBound << " and "
                      << maxBound << ")" << std::endl;
            exit(1);
        };

        if (value < minBound)
            error("is too small");
        if (value > maxBound)
            error("is too big");
    };
}

static po::options_description getUsage(void) {
    po::options_description usage { "Available options" };

    usage.add_options()
        ("help",        "Show this help message")
        ("width,w",     po::value(&GameOptions::width)
                            -> notifier(validateRange(10, 192, "width")),
                        "The width of the game arena")
        ("height,h",    po::value(&GameOptions::height)
                            -> notifier(validateRange(10, 108, "height")),
                        "The height of the game arena")
        ("torus,t",     po::bool_switch(&GameOptions::torus),
                        "Torus mode")
        ("snakes,s",    po::value(&GameOptions::snakeCount)
                            -> notifier(validateRange(1, 4, "snakes")),
                        "Number of snakes")
        ("players,p",   po::value(&GameOptions::playerCount)
                            -> notifier(validateRange(0, 4, "players")),
                        "Number of players")
        ("script",      po::value(&GameOptions::aiFile),
                        "Python script file for AIs")
        ("client",      po::bool_switch(&GameOptions::client),
                        "Join a multiplayer game")
        ("server",      po::bool_switch(&GameOptions::server),
                        "Host a multiplayer game")
        ("host",        po::value(&GameOptions::host),
                        "The host address of the multiplayer game to join")
        ("port",        po::value(&GameOptions::port),
                        "The port of the multiplayer game to host/join")
    ;

    return usage;
}

void GameOptions::parseFromCommandLine(int argc, char **argv) {
    po::variables_map options;
    po::command_line_parser parser { argc, argv };

    auto usage = getUsage();
    try {
        po::store(parser.options(usage).run(), options);
        if (options.count("help")) {
            std::cerr << usage << std::endl;
            exit(0);
        }
        po::notify(options);
    }
    catch (const po::error & exception) {
        std::cerr << exception.what() << std::endl << std::endl;
        std::cerr << usage << std::endl;
        exit(1);
    }
}
