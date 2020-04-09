#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <new>

namespace ros {

template <class T>
class refptr {
 private:
  struct Reference {
    size_t count;
    int byte0;  // beginning of object container
  };

  Reference* reference;

  T* ptr_unchecked() { return reinterpret_cast<T*>(&reference->byte0); }
  T const* const ptr_unchecked() const { return reinterpret_cast<T const* const>(&reference->byte0); }

  T* ptr() {
    assert(reference->count);
    return ptr_unchecked();
  }

  T const* const ptr() const {
    assert(reference->count);
    return ptr_unchecked();
  }

  void increment() {
    assert(reference);
    ++reference->count;
  }

  void decrement() {
    if (reference) {
      assert(reference->count);
      --reference->count;
      if (reference->count == 0) {
        // call destructor of T
        ptr_unchecked()->~T();
        std::free(reference);
        reference = nullptr;
      }
    }
  }

 public:
  // construct new object with parameter
  template <class... Ts>
  refptr(Ts... args) {
    enum { CONTAINER_SIZE = sizeof(size_t) + sizeof(T) };
    reference = reinterpret_cast<Reference*>(std::malloc(CONTAINER_SIZE));
    reference->count = 1;
    new (ptr()) T(args...);  // construct new Object at adress of container
  }

  // copy
  refptr(const refptr<T>& rhs) : reference(rhs.reference) { increment(); }

  // move
  refptr(refptr<T>&& rhs) : reference(rhs.reference) { rhs.reference = nullptr; }

  // destructor
  ~refptr() { decrement(); }

  T* operator->() { return ptr(); }
  T& operator*() { return *ptr(); }
  const T* operator->() const { return ptr(); }
  const T& operator*() const { return *ptr(); }

  refptr<T>& operator=(const refptr<T>&) = delete;
  const refptr<T>& operator=(const refptr<T>&) const = delete;
};

}  // namespace ros
