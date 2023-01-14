#pragma once

#include <rose/assert.h>
#include <rose/reflection.h>
#include <rose/internal/bindings_subsystem.h>

namespace rose::world {
    // Not implemented by default.
    // Must be specialized in corresponding
    // object header when code is generated.
    template <typename T>
    rose::reflection::TypeInfo get_type_info();

    template<class T>
    T & get() {
        rose::reflection::TypeInfo info = get_type_info<T>();
        void * ptr = c_rose_internal_lazy_regsiter_or_fetch_worldstate(info);
        assert(ptr);
        return *reinterpret_cast<T*>(ptr);
    }
}