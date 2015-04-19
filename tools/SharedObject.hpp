#pragma once

#include <dlfcn.h>

#include <memory>
#include <string>
#include <functional>
#include <system_error>

template <
    class Interface,
    class SOInfo = typename Interface::SharedObjectInfo
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
        auto getterFn = reinterpret_cast<typename SOInfo::Getter>(
            dlsym(handle_, SOInfo::getterName)
        );
        char *error = dlerror();
        if (error)
            throw std::system_error { std::error_code{}, error };

        // Binding getter with its arguments
        initF_ = std::bind(getterFn, args...);
    }

    ~SharedObject(void) {
        release();
        dlclose(handle_);
    }

    // 42 norme
    SharedObject(void)                              = delete;
    SharedObject(const SharedObject &)              = delete;
    SharedObject & operator=(const SharedObject &)  = delete;
    //

    void init(void) {
        interface_.reset(initF_());
        if (!interface_)
            throw std::runtime_error { "Null shared object interface" };
    }

    Interface * get(void) {
        return interface_.get();
    }

    Interface * operator->(void) {
        return get();
    }

    void release(void) {
        interface_.reset();
    }

private:
    using InitF                 = std::function<Interface * (void)>;

    void                        *handle_;
    InitF                       initF_;
    std::unique_ptr<Interface>  interface_;

};
