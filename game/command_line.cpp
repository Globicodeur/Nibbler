#include "command_line.hpp"
#include "GameEngine.hpp"

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

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
        ("width,w",     po::value(&GameEngine::width)
                            -> required()
                            -> notifier(validateRange(10, 192, "width")),
                        "The width of the game arena")
        ("height,h",    po::value(&GameEngine::height)
                            -> required()
                            -> notifier(validateRange(10, 108, "height")),
                        "The height of the game arena")
        ("torus,t",     po::bool_switch(&GameEngine::torus)
                            -> default_value(false),
                        "Torus mode")
    ;

    return usage;
}

void parseCommandLine(int argc, char **argv) {
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
