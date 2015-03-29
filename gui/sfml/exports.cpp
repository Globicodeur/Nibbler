#include "Canvas.hpp"

extern "C" {

    gui::Canvas * get(unsigned width, unsigned height) {
        return new SFMLCanvas { width, height };
    }

}
