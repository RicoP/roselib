#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <new>

namespace ros {

template <class T>
class refptr {
  struct Reference {
    size_t count;
    int byte0;  // beginning of object container

    T* ptr_unchecked() { return reinterpret_cast<T*>(&byte0); }
    const T* ptr_unchecked() const { return reinterpret_cast<const T*>(&byte0); }

    T* ptr() {
      assert(count);
      return ptr_unchecked();
    }

    const T* ptr() const {
      assert(count);
      return ptr_unchecked();
    }
  };

  Reference* reference;

  void increment() {
    assert(reference && reference->count);
    ++reference->count;
  }

  void decrement() {
    if (reference) {
      assert(reference->count);
      --reference->count;
      if (reference->count == 0) {
        // call destructor of T
        reference->ptr_unchecked()->~T();
        std::free(reference);
        reference = nullptr;
      }
    }
  }

  template <class... Ts>
  static Reference* make_reference(Ts... args) {
    enum { CONTAINER_SIZE = sizeof(size_t) + sizeof(T) };
    Reference* reference = reinterpret_cast<Reference*>(std::malloc(CONTAINER_SIZE));
    reference->count = 1;
    new (&reference->byte0) T(args...);  // construct new Object at adress of container
    return reference;
  }

 public:
  constexpr refptr() : reference(nullptr) {}

  // construct new object with parameter
  template <class... Ts>
  refptr(Ts... args) {
    reference = make_reference(args...);
  }

  // copy
  refptr(const refptr<T>& rhs) : reference(rhs.reference) { increment(); }

  // move
  refptr(refptr<T>&& rhs) : reference(rhs.reference) { rhs.reference = nullptr; }

  // destructor
  ~refptr() { release(); }

  // static make function. Necessary for constructors with zero parameter.
  template <class... Ts>
  static refptr<T> make(Ts... args) {
    refptr<T> p;
    p.reference = make_reference(args...);
    return p;
  }

  size_t use_count() const { return reference ? reference->count : 0; }

  void release() {
    decrement();
    reference = nullptr;
  }

  T* operator->() {
    assert(reference);
    return reference->ptr();
  }

  T& operator*() {
    assert(reference);
    return *reference->ptr();
  }

  const T* operator->() const {
    assert(reference);
    return reference->ptr();
  }

  const T& operator*() const {
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
  const refptr<T>& operator=(const refptr<T>&) const = delete;

  // view for circular references
  class refview {
    Reference* reference;

   public:
    refview() : reference(nullptr) {}

    refview(refptr<T>& ptr) : reference(ptr.reference) {}
    refview(refptr<T>&& ptr) : reference(ptr.reference) {}

    refview(refview& ptr) : reference(ptr.reference) { ptr.reference = nullptr; }
    refview(refview&& ptr) : reference(ptr.reference) { ptr.reference = nullptr; }

    refview& operator=(refptr<T>& rhs) {
      reference = rhs.reference;
      return *this;
    }

    refview& operator=(refptr<T>&& rhs) {
      reference = rhs.reference;
      return *this;
    }

    T* operator->() {
      assert(reference);
      return reference->ptr();
    }

    T& operator*() {
      assert(reference);
      return *reference->ptr();
    }

    const T* operator->() const {
      assert(reference);
      return reference->ptr();
    }

    const T& operator*() const {
      assert(reference);
      return *reference->ptr();
    }
  };
};

}  // namespace ros
