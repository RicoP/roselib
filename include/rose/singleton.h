#pragma once

#include <new> //std::launder
#include <type_traits> // std::is_base_of
#include <rose/assert.h>
#include <rose/nocopy.h>
#include <rose/reflection.h>

namespace rose::internal {

// Returns the substring at the tail end of 'skip'. Returns the original string when string doesn't contain skip.
constexpr const char* string_tail_end(const char* string, const char* skip) {
  int i = 0;
  int j = 0;

  while (string[i]) {
    if (skip[j] == 0) {
      return string + i - 1; // -1 so we point on the last character of 'skip'
    }
    if (string[i] == skip[j]) {
      j++;
    } else {
      if (j != 0) {
        j = 0;
        continue;
      }
    }
    i++;
  }
  return string;
}

// test string_tail_end
static_assert(rose::hash(string_tail_end("Hello/World", "/")) == rose::hash("/World"), "test failed");
static_assert(rose::hash(string_tail_end("Hello/World", "/")) != rose::hash("Hello"), "test failed");
static_assert(rose::hash(string_tail_end("Hello/foo/World", "/foo/")) == rose::hash("/World"), "test failed");
static_assert(rose::hash(string_tail_end("World", "/foo/")) == rose::hash("World"), "test failed");
static_assert(rose::hash(string_tail_end(string_tail_end("Hello/foo/bar/World", "/foo/"), "/bar/")) == rose::hash("/World"), "test failed");

constexpr rose::hash_value hash_path(const char* path, rose::hash_value line = 0) {
  path = string_tail_end(path, "/include/");
  path = string_tail_end(path, "/source/");
  path = string_tail_end(path, "\\include\\");
  path = string_tail_end(path, "\\source\\");

  // https://de.wikipedia.org/wiki/FNV_(Informatik)#FNV-Implementation,_64-bit-Schl%C3%BCssel
  rose::hash_value MagicPrime = 0x00000100000001b3ULL;
  rose::hash_value Hash = 0xcbf29ce484222325ULL;

  for (; *path; path++) {
    char c = *path;
    if(c == '\\') c = '/';
    Hash = (Hash ^ c) * MagicPrime;
  }

  return Hash ^ line;
}

// test hash_path
static_assert(hash_path("C:\\Hello.h") == hash_path("C:/Hello.h"), "test failed");
static_assert(hash_path("A/include/Hello.h") == hash_path("/Hello.h"), "test failed");
static_assert(hash_path("A/include/Hello.h") == hash_path("A\\include\\Hello.h"), "test failed");
static_assert(hash_path("A/source/Hello.h") == hash_path("/Hello.h"), "test failed");
static_assert(hash_path("A/include/Hello.h") == hash_path("/Hello.h"), "test failed");
static_assert(hash_path("A/include/Hello.h") == hash_path("A/source/Hello.h"), "test failed");
static_assert(hash_path("A/include/A") == hash_path("A\\source\\A"), "test failed");
static_assert(hash_path("A/include/A") != hash_path("A/source/B"), "test failed");

struct RoseSingletonImplBase : rose::nocopy {};

template <rose::hash_value UNIQUE_ID>
struct RoseSingletonImpl : RoseSingletonImplBase {
    static inline rose::hash_value type_id = UNIQUE_ID;

    /// all instances of RoseUtilityRegister must be virtual
    virtual ~RoseSingletonImpl() {}
};

template <typename T>
struct RoseSingletonSingleton {
  static T& instance() { return rose::world::get_singleton<T>(); }
};

}

namespace rose::world {
    template <class T>
    void register_singleton(T* instance) {
      static_assert(std::is_base_of<rose::internal::RoseSingletonImplBase, T>::value, "T must inherit from RoseSingleton");
      assert(instance);
      c_rose_internal_register_singleton_class_instance(c_rose_subsystem_instance_id, T::type_id, instance);
    }

    template <class T>
    void unregister_singleton(T* instance) {
      static_assert(std::is_base_of<rose::internal::RoseSingletonImplBase, T>::value, "T must inherit from RoseSingleton");
      assert(instance);
      c_rose_internal_unregister_singleton_class_instance(c_rose_subsystem_instance_id, T::type_id, instance);
    }

    template<class T>
    T & get_singleton() {
        void * ptr = c_rose_internal_get_singleton_class_instance(c_rose_subsystem_instance_id, T::type_id);
        assert(ptr);
        return *std::launder(reinterpret_cast<T*>(ptr));
    }
}

#define RoseSingleton \
  rose::internal::RoseSingletonImpl<rose::internal::hash_path(__FILE__, __LINE__)>, rose::internal::RoseSingletonSingleton
