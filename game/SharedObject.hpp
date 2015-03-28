#pragma once

#include <dlfcn.h>
#include <iostream>
#include <memory>

template <class Interface, class GetterFn, const char * GetterFnName>
class SharedObject {

public:
    template <class... GetterArgs>
    SharedObject(const std::string & objectName, const GetterArgs &... args) {
        handle_ = dlopen(objectName.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!handle_)
            std::cerr << dlerror() << std::endl;

        char *error;
        auto getterFn = reinterpret_cast<GetterFn>(dlsym(handle_, GetterFnName));
        if ((error = dlerror()) != nullptr)
            std::cerr << error << std::endl;

        interface_.reset(getterFn(args...));
    }

    ~SharedObject() {
        if (handle_) {
            interface_.reset();
            dlclose(handle_);
        }
    }

    Interface * get() const {
        return interface_.get();
    }

private:
    void                        *handle_;
    std::unique_ptr<Interface>  interface_;

};
