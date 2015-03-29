#pragma once

#include <dlfcn.h>

#include <memory>
#include <functional>
#include <system_error>

template <class Interface, class GetterFn, const char * getterFnName>
class SharedObject {

public:
    template <class... GetterArgs>
    SharedObject(const std::string & objectName, const GetterArgs &... args):
        handle_ { nullptr } {

        handle_ = dlopen(objectName.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!handle_)
            throw std::system_error { std::error_code{}, dlerror() };

        char *error;
        auto getterFn = reinterpret_cast<GetterFn>(dlsym(handle_, getterFnName));
        if ((error = dlerror()) != nullptr)
            throw std::system_error { std::error_code{}, error };

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
