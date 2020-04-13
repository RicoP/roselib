#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <new>

namespace ros {
constexpr std::uint64_t i_am_ok = 30240007572758601UL;

template <class T>
class refptr {
  struct Reference {
    size_t count;
    std::uint64_t check;  // checksum to find bad pointer
    int byte0;            // beginning of object container

    T* ptr_unchecked() noexcept { return reinterpret_cast<T*>(&byte0); }
    const T* ptr_unchecked() const noexcept { return reinterpret_cast<const T*>(&byte0); }

    T* ptr() noexcept {
      assert(count);
      assert(check == i_am_ok);
      return ptr_unchecked();
    }

    const T* ptr() const noexcept {
      assert(count);
      assert(check == i_am_ok);
      return ptr_unchecked();
    }

    size_t use_count() const noexcept {
      assert(check == i_am_ok);
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
        reference->check = 0;
        // call destructor of T
        reference->ptr_unchecked()->~T();
        std::free(reference);
        reference = nullptr;
      }
    }
  }

  template <class... Ts>
  static Reference* make_reference(Ts... args) {
    enum { CONTAINER_SIZE = sizeof(size_t) + sizeof(uint64_t) + sizeof(T) };
    Reference* reference = reinterpret_cast<Reference*>(std::malloc(CONTAINER_SIZE));
    reference->count = 1;
    reference->check = i_am_ok;
    new (&reference->byte0) T(args...);  // construct new Object at adress of container
    return reference;
  }

 public:
  constexpr refptr() noexcept : reference(nullptr) {}

  // construct new object with parameter
  template <class... Ts>
  refptr(Ts... args) {
    reference = make_reference(args...);
  }

  // copy
  refptr(const refptr<T>& rhs) noexcept : reference(rhs.reference) { increment(); }

  // move
  refptr(refptr<T>&& rhs) noexcept : reference(rhs.reference) { rhs.reference = nullptr; }

  // destructor
  ~refptr() { release(); }

  // static make function. Necessary for constructors with zero parameter.
  template <class... Ts>
  static refptr<T> make(Ts... args) {
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
    decrement();
    reference = rhs.reference;
    increment();
    return *this;
  }

  refptr<T>& operator=(refptr<T>&& rhs) {
    assert(rhs.reference != nullptr);
    release();
    reference = rhs.reference;
    rhs.reference = nullptr;
    return *this;
  }

  const refptr<T>& operator=(const refptr<T>&) const = delete;

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
