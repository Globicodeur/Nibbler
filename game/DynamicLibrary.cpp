#include "DynamicLibrary.hpp"

DynamicLibrary::DynamicLibrary(const std::string & name):
    handle_(nullptr)
{
    handle_ = dlopen(name.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!handle_) {
        std::cerr << dlerror() << std::endl;
        isValid_ = false;
    }
    else {
        isValid_ = true;
        isValid_ &= dlsymSafe(handle_, init, "init");
        isValid_ &= dlsymSafe(handle_, clean, "clean");
        isValid_ &= dlsymSafe(handle_, draw, "draw");
        isValid_ &= dlsymSafe(handle_, getInput, "getInput");
    }
}

DynamicLibrary::~DynamicLibrary()
{
    if (handle_)
        dlclose(handle_);
}

bool DynamicLibrary::isValid() const
{
    return isValid_;
}
