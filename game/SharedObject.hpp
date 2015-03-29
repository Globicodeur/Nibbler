#pragma once

#include <dlfcn.h>

#include <memory>
#include <functional>
#include <system_error>

template <
    class Interface,
    class GetterFn = typename Interface::SharedObjectInfo::Getter,
    const char * getterFnName = Interface::SharedObjectInfo::GETTER_NAME
>
class SharedObject {

public:
    template <class... GetterArgs>
    SharedObject(const std::string & objectName, const GetterArgs &... args) {
        // Acquiring object handle
        handle_ = dlopen(objectName.c_str(), RTLD_NOW | RTLD_LOCAL);
        if (!handle_)
            throw std::system_error { std::error_code{}, dlerror() };

        // Acquiring the interface creation function
        auto getterFn = reinterpret_cast<GetterFn>(
            dlsym(handle_, getterFnName)
        );
        char *error = dlerror();
        if (error)
            throw std::system_error { std::error_code{}, error };

        // Binding getter with its arguments
        initF_ = std::bind(getterFn, args...);
    }

    ~SharedObject() {
        release();
        dlclose(handle_);
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
    using InitF                 = std::function<Interface * ()>;

    void                        *handle_;
    InitF                       initF_;
    std::unique_ptr<Interface>  interface_;

};
