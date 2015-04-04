#include "PythonWrapper.hpp"
#include "GameOptions.hpp"

#include "Snake.hpp"

BOOST_PYTHON_MODULE(snake)
{
    bp::class_<Snake>("Snake", bp::no_init)
        .def("turn", &Snake::turn)
        ;

    bp::enum_<Direction>("Direction")
        .value("Up", Up)
        .value("Down", Down)
        .value("Left", Left)
        .value("Right", Right)
        ;
}

Python::Python(void) {
    Py_Initialize();
    initsnake();

    globals_ = bp::import("__main__").attr("__dict__");
    try {
        bp::exec_file(GameOptions::aiFile.c_str(), globals_);
    }
    catch(...) {
        PyErr_Print();
        exit(1);
    }
}

Python::~Python(void) {
    Py_Finalize();
}

Python & Python::instance(void) {
    static Python python;
    return python;
}
