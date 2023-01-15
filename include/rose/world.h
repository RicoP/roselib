#pragma once

#include <new> //std::launder
#include <rose/assert.h>
#include <rose/reflection.h>
#include <rose/internal/bindings_subsystem.h>

namespace rose::world {
    template<class T>
    T & get() {
        rose::reflection::TypeInfo info = rose::reflection::get_type_info<T>();
        void * ptr = c_rose_internal_create_or_fetch_worldstate(c_rose_subsystem_instance_id, info);
        assert(ptr);
        return *std::launder(reinterpret_cast<T*>(ptr));
    }
}