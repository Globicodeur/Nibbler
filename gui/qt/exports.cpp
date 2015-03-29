#include "Canvas.hpp"

extern "C" {

    gui::Canvas * get(unsigned width, unsigned height) {
        return new QtCanvas { width, height };
    }

}

static_assert(
    std::is_same<
        decltype(&get),
        gui::Canvas::SharedObjectInfo::Getter
    >::value,
    "Invalid exported function"
);
