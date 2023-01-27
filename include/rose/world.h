#pragma once

#include <new> //std::launder
#include <type_traits> // std::is_base_of
#include <rose/assert.h>
#include <rose/reflection.h>

namespace rose::internal {
constexpr rose::hash_value RoseUniqueClassImplHash(const char* file, rose::hash_value line) {
  rose::hash_value MagicPrime = 0x00000100000001b3ULL;
  rose::hash_value Hash = 0xcbf29ce484222325ULL;

  for (; *file; file++) {
    char c = *file;
    if(c == '\\') c = '/';
    Hash = (Hash ^ c) * MagicPrime;
  }

  return Hash ^ line;
}

struct RoseUniqueClassImplBase {};

template <rose::hash_value UNIQUE_ID>
struct RoseUniqueClassImpl : RoseUniqueClassImplBase {
    static inline char* file = __FILE__;
    static inline rose::hash_value type_id = UNIQUE_ID;
};
}

// TODO: Wrap 'rose::hash(__FILE__)' in a constexpr function that only takes
//       the part after '/include/' or '/source/' so the same source file
//       generates the same ID on different machines.
#define RoseUniqueClass rose::internal::RoseUniqueClassImpl<rose::internal::RoseUniqueClassImplHash(__FILE__, __LINE__)>

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
        c_rose_internal_register_utility_class_instance(c_rose_subsystem_instance_id, T::type_id, instance);
    }

    template<class T>
    T & get_utility() {
        void * ptr = c_rose_internal_get_utility_class_instance(c_rose_subsystem_instance_id, T::type_id);
        assert(ptr);
        return *std::launder(reinterpret_cast<T*>(ptr));
    }
}
