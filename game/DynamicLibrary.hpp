#pragma once

#include <dlfcn.h>
#include <iostream>

#include "gui/spec.hpp"

template<class T>
bool        dlsymSafe(void *handle, T & symbol, const char *toGet) {
    char    *error;

    symbol = reinterpret_cast<T>(dlsym(handle, toGet));
    if ((error = dlerror()) != nullptr)  {
        std::cerr << error << std::endl;
        return false;
    }
    return true;
}

class DynamicLibrary {

    using init_t        = void (*)(unsigned, unsigned);
    using clean_t       = void (*)();
    using draw_t        = void (*)(const gui::GameInfo &);
    using getInput_t    = gui::InputType (*)();

public:
    DynamicLibrary(const std::string & name);
    ~DynamicLibrary();

    init_t                  init;
    clean_t                 clean;
    draw_t                  draw;
    getInput_t              getInput;

    bool isValid() const;

private:
    DynamicLibrary();
    DynamicLibrary(const DynamicLibrary &);
    DynamicLibrary & operator=(const DynamicLibrary &);

    void                    *handle_;
    bool                    isValid_;
};
