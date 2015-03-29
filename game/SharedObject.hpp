#pragma once

#include <dlfcn.h>
#include <iostream>
#include <memory>
#include <functional>

template <class Interface, class GetterFn, const char * getterFnName>
class SharedObject {

public:
    template <class... GetterArgs>
    SharedObject(const std::string & objectName, const GetterArgs &... args):
        handle_ { nullptr } {

        handle_ = dlopen(objectName.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!handle_)
            std::cerr << dlerror() << std::endl;

        char *error;
        auto getterFn = reinterpret_cast<GetterFn>(dlsym(handle_, getterFnName));
        if ((error = dlerror()) != nullptr)
            std::cerr << error << std::endl;

        initF_ = std::bind(getterFn, args...);
    }

    ~SharedObject() {
        if (handle_) {
            release();
            dlclose(handle_);
        }
    }

    Interface * get() {
        if (!interface_)
            interface_.reset(initF_());
        return interface_.get();
    }

    void release() {
        interface_.reset();
    }

private:
    using InitF = std::function<Interface * ()>;

    void                        *handle_;
    InitF                       initF_;
    std::unique_ptr<Interface>  interface_;

};
