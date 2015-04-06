#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "../Snake.hpp"
#include "../GameOptions.hpp"

namespace bp = boost::python;

template <class T>
static void registerVector() {
    bp::class_<std::vector<T>>("CustomVector", bp::no_init)
        .def(bp::vector_indexing_suite<std::vector<T>>{})
        ;
}

BOOST_PYTHON_MODULE(snake)
{
    using ReturnByReference =
        bp::return_value_policy<bp::reference_existing_object>;

    registerVector<Position>();
    registerVector<Snake::Body>();

    bp::class_<Position>("Position")
        .def(bp::init<int, int>{})
        .def_readonly("x", &Position::x)
        .def_readonly("y", &Position::y)
        .def("__add__", &Position::operator+)
        ;

    bp::class_<Snake>("Snake", bp::no_init)
        .def("head", &Snake::head, ReturnByReference{})
        .def("body", &Snake::body, ReturnByReference{})
        .def("turn", &Snake::turn)
        .def_readonly("direction", &Snake::direction)
        ;

    bp::enum_<Direction>("Direction")
        .value("Up", Up)
        .value("Down", Down)
        .value("Left", Left)
        .value("Right", Right)
        ;

    bp::class_<GameOptions>("GameOptions", bp::no_init)
        .add_static_property("width", bp::make_getter(&GameOptions::width))
        .add_static_property("height", bp::make_getter(&GameOptions::height))
        .add_static_property("torus", bp::make_getter(&GameOptions::torus))
        .add_static_property("snake_count", bp::make_getter(&GameOptions::snakeCount))
        ;
}
