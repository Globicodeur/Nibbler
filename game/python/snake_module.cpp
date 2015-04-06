#include <boost/python.hpp>

#include "../Snake.hpp"

BOOST_PYTHON_MODULE(snake)
{
    namespace bp = boost::python;

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
