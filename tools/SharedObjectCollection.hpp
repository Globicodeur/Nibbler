#pragma once

#include <cstdlib>

#include "SharedObject.hpp"

template <class Interface>
class SharedObjectCollection {
    using Object    = SharedObject<Interface>;
    using Objects   = std::vector<std::unique_ptr<Object>>;

public:
    SharedObjectCollection(void):
        currentObject_ { nullptr }
    { }
    ~SharedObjectCollection(void) = default;

    template <class... Args, size_t n>
    void load(const char * (&libraryNames)[n], const Args &... args) {
        for (auto name: libraryNames)
            objects_.emplace_back(new Object { name, args... });
        swap(rand() % n);
    }

    void swap(size_t i) {
        if (i < objects_.size()) {
            auto newObject = objects_.at(i).get();
            if (newObject != currentObject_) {
                if (currentObject_)
                    currentObject_->release();
                currentObject_ = newObject;
            }
        }
    }

    Interface * operator->(void) {
        return currentObject_->get();
    }

private:
    Object          *currentObject_;
    Objects         objects_;
};