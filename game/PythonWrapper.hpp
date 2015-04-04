#pragma once

#include <locale> // OSX python2.7 pyport.h workaround
#include <boost/python.hpp>
namespace bp = boost::python;

class Python {

public:
                        Python(void);
                        ~Python(void);

    static Python &     instance(void);

                        Python(const Python &) = delete;
    Python &            operator=(const Python &) = delete;

    template <class F>
    static void         exec(const F & f) {
        try {
            f(instance().globals_);
        }
        catch(const bp::error_already_set &) {
            PyErr_Print();
        }
    }

private:
    bp::object  globals_;

};
