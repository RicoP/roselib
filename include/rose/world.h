#pragma once

#include <new> //std::launder
#include <type_traits> // std::is_base_of
#include <rose/assert.h>
#include <rose/reflection.h>

namespace rose::internal {
constexpr rose::hash_value RoseUniqueClassImplHash(const char* file, rose::hash_value line = 0) {
  rose::hash_value MagicPrime = 0x00000100000001b3ULL;
  rose::hash_value Hash = 0xcbf29ce484222325ULL;

  int state = 0;
  for (; *file; file++) {
    char c = *file;
    if(c == '\\') c = '/';


    switch (state) {
      break; case  '/': state = c == 'i' ? 'ii' : '/';
      break; case 'ii': state = c == 'n' ? 'in' : 0;
      break; case 'in': state = c == 'c' ? 'ic' : 0;
      break; case 'ic': state = c == 'l' ? 'il' : 0;
      break; case 'il': state = c == 'u' ? 'iu' : 0;
      break; case 'iu': state = c == 'd' ? 'id' : 0;
      break; case 'id': state = c == 'e' ? 'ie' : 0;
      break; case 'ie': state = 0; if(c == '/') Hash = 0xcbf29ce484222325ULL; 
    }

    switch (state) {
      break; case  '/': state = c == 's' ? 'ss' : 0;
      break; case 'ss': state = c == 'o' ? 'so' : 0;
      break; case 'so': state = c == 'u' ? 'su' : 0;
      break; case 'su': state = c == 'r' ? 'sr' : 0;
      break; case 'sr': state = c == 'c' ? 'sc' : 0;
      break; case 'sc': state = c == 'e' ? 'se' : 0;
      break; case 'se': state = 0; if(c == '/') Hash = 0xcbf29ce484222325ULL; 
    }

    if (state == 0 && c == '/') state = '/';
    Hash = (Hash ^ c) * MagicPrime;
  }

  return Hash ^ line;
}

//Some tests
static_assert(RoseUniqueClassImplHash("C:\\Hello.h") == RoseUniqueClassImplHash("C:/Hello.h"), "test failed");
static_assert(RoseUniqueClassImplHash("A/include/Hello.h") == RoseUniqueClassImplHash("/Hello.h"), "test failed");
static_assert(RoseUniqueClassImplHash("A/include/Hello.h") == RoseUniqueClassImplHash("A/source/Hello.h"), "test failed");
static_assert(RoseUniqueClassImplHash("A/include/Hello.h") == RoseUniqueClassImplHash("A/source/include/source/Hello.h"), "test failed");
static_assert(RoseUniqueClassImplHash("A/source/Hello.h") == RoseUniqueClassImplHash("/Hello.h"), "test failed");
static_assert(RoseUniqueClassImplHash("A/include/A") != RoseUniqueClassImplHash("A/source/B"), "test failed");

struct RoseUniqueClassImplBase {};

template <rose::hash_value UNIQUE_ID>
struct RoseUniqueClassImpl : RoseUniqueClassImplBase {
    static inline char* file = __FILE__;
    static inline rose::hash_value type_id = UNIQUE_ID;
};
}

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
