#include <iostream>

#include "Application.hpp"

int main(int argc, char **argv) {

    srand(time(nullptr));

    Application app { argc, argv };

    try {
        app.run();
    }
    catch(const std::exception & exception) {
        std::cerr << exception.what() << std::endl;
        return 1;
    }

    return 0;
}
