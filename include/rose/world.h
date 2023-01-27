#pragma once

#include <new> //std::launder
#include <type_traits> // std::is_base_of
#include <rose/assert.h>
#include <rose/reflection.h>
#include <rose/internal/bindings_subsystem.h>

namespace rose::internal {
struct RoseUniqueClassImplBase {};

template <const char * TFILE, int TLINE>
struct RoseUniqueClassImpl : RoseUniqueClassImplBase {
    // TODO: Wrap 'rose::hash(__FILE__)' in a constexpr function that only takes
    //       the part after '/include/' or '/source/' so the same source file
    //       generates the same ID on different machines.
    enum { class_id = rose::hash(TFILE) ^ TLINE };
    const char * file = TFILE;
    int line = TLINE;
};
}

#define RoseUniqueClass rose::internal::RoseUniqueClassImpl<__FILE__, __LINE__>

namespace rose::world {
    template<class T>
    T & get() {
        auto & info = rose::reflection::get_type_info<T>();
        void * ptr = c_rose_internal_create_or_fetch_worldstate(c_rose_subsystem_instance_id, info);
        assert(ptr);
        return *std::launder(reinterpret_cast<T*>(ptr));
    }

    template<class T>
    void register_utility(T * instance) {
        static_assert( std::is_base_of<rose::internal::RoseUniqueClassImplBase, T>::value, "T must enherit from RoseUniqueClass" );
        assert(instance);
        rose::hash_value type_id = T::class_id;
        c_rose_internal_register_utility_class_instance(c_rose_subsystem_instance_id, type_id, instance);
    }

    template<class T>
    T & get_utility() {
        rose::hash_value type_id = T::class_id;
        void * ptr = c_rose_internal_get_utility_class_instance(c_rose_subsystem_instance_id, type_id);
        assert(ptr);
        return *std::launder(reinterpret_cast<T*>(ptr));
    }
}
