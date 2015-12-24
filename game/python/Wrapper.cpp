#include "Wrapper.hpp"

#include "../GameOptions.hpp"

#include <future>
#include <iostream>
#include <fstream>
#include <streambuf>

extern "C" void initsnake(void);

Python::Python(void) {
    Py_Initialize();
    PyEval_InitThreads();

    initsnake();

    globals_ = bp::import("__main__").attr("__dict__");

    try {
        std::ifstream file { GameOptions::aiFile.c_str() };
        std::string code {
            std::istreambuf_iterator<char> { file },
            std::istreambuf_iterator<char> { }
        };
        bp::exec(code.c_str(), globals_);
    }
    catch(...) {
        PyErr_Print();
        exit(1);
    }
    mainThreadState_ = PyEval_SaveThread();
}

Python::~Python(void) {
    PyEval_RestoreThread(mainThreadState_);
    Py_Finalize();
}

Python & Python::instance(void) {
    static Python python;
    return python;
}

void Python::execImpl(std::function<void ()> f, unsigned timeout) {
    std::packaged_task<void ()> task ([func = std::move(f)]{
        GILLocker lock;
        try {
            func();
        }
        catch (...) {
            PyErr_Print();
        }
    });
    auto future = task.get_future();
    std::thread pyThread { std::move(task) };

    auto status = future.wait_for(std::chrono::milliseconds { timeout });
    if (status == std::future_status::ready)
        pyThread.join();
    else {
        std::cerr << "Python script timed out after "
                  << timeout << " milliseconds" << std::endl;
        pyThread.detach();
        exit(1);
    }
}

Python::GILLocker::GILLocker(void):
    state_ { PyGILState_Ensure() }
{ }

Python::GILLocker::~GILLocker(void) {
    PyGILState_Release(state_);
}
