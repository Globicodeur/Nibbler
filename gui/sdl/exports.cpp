#include "Canvas.hpp"

extern "C" {

    gui::Canvas * get(unsigned width, unsigned height) {
        return new SDLCanvas { width, height };
    }

}

static_assert(
    std::is_same<
        decltype(&get),
        gui::Canvas::SharedObjectInfo::Getter
    >::value,
    "Invalid exported function"
);
