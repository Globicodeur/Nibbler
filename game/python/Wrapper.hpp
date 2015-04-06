#pragma once

#include <locale> // OSX python2.7 pyport.h workaround
#include <functional>
#include <boost/python.hpp>
namespace bp = boost::python;

class Python {

public:
                        Python(void);
                        ~Python(void);
                        Python(const Python &)      = delete;
    Python &            operator=(const Python &)   = delete;
    static Python &     instance(void);

    template <class F>
    static void         exec(const F & f, unsigned timeout=-1u) {
        execImpl(std::bind(f, instance().globals_), timeout);
    }

private:
    bp::object          globals_;
    PyThreadState       *mainThreadState_;

    static void         execImpl(std::function<void ()> f, unsigned timeout);

    class GILLocker {

    public:
                            GILLocker(void);
                            ~GILLocker(void);
        // 42 norme
                            GILLocker(const GILLocker &)    = delete;
    GILLocker &             operator=(const GILLocker &)    = delete;
        //
    private:
        PyGILState_STATE    state_;
    };
};
