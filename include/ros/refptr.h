#pragma once

//DEPRECATED for now because it causes some issues in glmovement:af0512ce4ccf9925fcc66ae7257fc39fac7552f9

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>
#include <type_traits>

#ifdef _WIN32
#  include <malloc.h>  //_aligned_malloc, _aligned_free
#endif

#ifdef ROS_LOG_REFPTR
// when you wanna log refptr then you must define g_refptr_line in ONE cpp file
extern int g_refptr_line;
#  define LOG(frmt, ...) printf("%d\t>" frmt, 0, __VA_ARGS__)
#else
#  define LOG(...)
#endif

namespace ros {

namespace internal {
  typedef unsigned long long ref_int;
  constexpr ref_int okay_check = 0x0'BAD'C0DE'BABE;
  constexpr size_t ideal_alignment = std::alignment_of<std::max_align_t>::value;

  static_assert(std::alignment_of<ref_int>::value == ideal_alignment, "ref_int is not most aligned");

// https://developercommunity.visualstudio.com/solutions/473365/view.html
#ifdef _WIN32
  // we always align our memory space to make sure the count and check members are
  // aligned, which is fine because we plan to use refptr for mostly "heavy" objects.
  inline void* refptr_aligned_alloc(size_t size) { return _aligned_malloc(size, ideal_alignment); }
  inline void refptr_aligned_free(void* ptr) { _aligned_free(ptr); }
#else
  inline void* refptr_aligned_alloc(size_t size) { return std::aligned_alloc(ideal_alignment, size); }
  inline void refptr_aligned_free(void* ptr) { std::free(ptr); }
#endif
}  // namespace internal

template <class T>
class refptr {
  struct Reference {
    internal::ref_int count;  // reference counter
    internal::ref_int check;  // checksum to find bad pointer
    internal::ref_int byte0;  // beginning of object container

    T* ptr_unchecked() noexcept { return reinterpret_cast<T*>(check == internal::okay_check ? &byte0 : 0); }
    const T* ptr_unchecked() const noexcept { return reinterpret_cast<const T*>(check == internal::okay_check ? &byte0 : 0); }

    T* ptr() noexcept {
      assert(count);
      assert(check == internal::okay_check);
      return ptr_unchecked();
    }

    const T* ptr() const noexcept {
      assert(count);
      assert(check == internal::okay_check);
      return ptr_unchecked();
    }

    size_t use_count() const noexcept {
      assert(check == internal::okay_check);
      return count;
    }
  };

  Reference* reference;

  void increment() noexcept {
    assert(reference);
    assert(reference->count);
    ++reference->count;
  }

  void decrement() {
    if (reference) {
      assert(reference->count);
      --reference->count;
      if (reference->count == 0) {
        LOG("count reached zero. dealloc \n");
        // call destructor of T
        reference->ptr_unchecked()->~T();
        reference->check = 0x0'DEAD'BABE'0000;
        internal::refptr_aligned_free(reference);
        reference = nullptr;
      }
    }
  }

  template <class... Ts>
  static Reference* make_reference(Ts... args) {
    enum { CONTAINER_SIZE = 2 * sizeof(internal::ref_int) + sizeof(T) };
    LOG("make_reference(%d) \n", CONTAINER_SIZE);
    Reference* reference = reinterpret_cast<Reference*>(internal::refptr_aligned_alloc(CONTAINER_SIZE));
    reference->count = 1;
    reference->check = internal::okay_check;
    new (&reference->byte0) T(args...);  // construct new Object at adress of container
    return reference;
  }

 public:
  constexpr refptr() noexcept : reference(nullptr) { LOG("refptr() \n"); }

  // construct new object with parameter
  template <class... Ts>
  refptr(Ts... args) {
    LOG("refptr(Ts... args) \n");
    reference = make_reference(args...);
  }

  // copy
  refptr(const refptr<T>& rhs) noexcept : reference(rhs.reference) {
    LOG("refptr(const refptr<T>& rhs) \n");
    increment();
  }

  // move
  refptr(refptr<T>&& rhs) noexcept : reference(rhs.reference) {
    LOG("refptr(refptr<T>&& rhs) \n");
    rhs.reference = nullptr;
  }

  // destructor
  ~refptr() {
    LOG("~refptr() %l \n", use_count());
    release();
  }

  // static make function. Necessary for constructors with zero parameter.
  template <class... Ts>
  static refptr<T> make(Ts... args) {
    LOG("make(Ts... args) \n");
    refptr<T> p;
    p.reference = make_reference(args...);
    return p;
  }

  size_t use_count() const noexcept { return reference ? reference->use_count() : 0; }

  void release() {
    decrement();
    reference = nullptr;
  }

  T* operator->() noexcept {
    assert(reference);
    return reference->ptr();
  }

  T& operator*() noexcept {
    assert(reference);
    return *reference->ptr();
  }

  const T* operator->() const noexcept {
    assert(reference);
    return reference->ptr();
  }

  const T& operator*() const noexcept {
    assert(reference);
    return *reference->ptr();
  }

  refptr<T>& operator=(refptr<T>& rhs) {
    assert(rhs.reference != nullptr);
    release();
    reference = rhs.reference;
    increment();
    return *this;
  }

  refptr<T>& operator=(refptr<T>&& rhs) noexcept {
    assert(rhs.reference);
    // we can actually just swap the two refrences because right after that the destructor of rhs will
    // be called, dealocating our old resource. Also this enables us marking this function as noexcept.
    std::swap(reference, rhs.reference);
    return *this;
  }

  const refptr<T>& operator=(const refptr<T>&) const = delete;

  operator bool() const { return reference != nullptr; }

  // view for circular references
  class refview {
    Reference* reference;

   public:
    size_t use_count() const noexcept { return reference ? reference->use_count() : 0; }

    refview() noexcept : reference(nullptr) {}

    refview(refptr<T>& ptr) noexcept : reference(ptr.reference) {}
    refview(refptr<T>&& ptr) noexcept : reference(ptr.reference) {}

    refview(refview& rhs) noexcept : reference(rhs.reference) { rhs.reference = nullptr; }
    refview(refview&& rhs) noexcept : reference(rhs.reference) { rhs.reference = nullptr; }

    refview& operator=(refptr<T>& rhs) noexcept {
      reference = rhs.reference;
      return *this;
    }

    refview& operator=(refptr<T>&& rhs) noexcept {
      reference = rhs.reference;
      return *this;
    }

    T* operator->() noexcept {
      assert(reference);
      return reference->ptr();
    }

    T& operator*() noexcept {
      assert(reference);
      return *reference->ptr();
    }

    const T* operator->() const noexcept {
      assert(reference);
      return reference->ptr();
    }

    const T& operator*() const noexcept {
      assert(reference);
      return *reference->ptr();
    }
  };
};

}  // namespace ros
