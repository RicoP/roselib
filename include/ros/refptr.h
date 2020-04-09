#include <assert.h>

namespace ros {

template <class T>
class refptr {
 private:
  struct Reference {
    size_t count;
    int byte0; //beginning of object container
  };

  Reference* reference;

  T* get_unchecked() { return reinterpret_cast<T*>(&reference->byte0); }
  T const* const get_unchecked() const { return reinterpret_cast<T*>(&reference->byte0); }

  T* get() {
    assert(reference->count);
    return get_unchecked();
  }

  T const* const get() const {
    assert(reference->count);
    return get_unchecked();
  }

  void increment() { ++reference->count; }

  void decrement() {
    if (reference) {
      assert(reference->count);
      --reference->count;
      if (reference->count == 0) {
        // call destructor of T
        get_unchecked()->~T();
        free(reference);
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
    new (&reference->byte0) T(args...);  // construct new Object at adress of container
  }

  // copy
  refptr(const refptr<T>& ptr) : reference(ptr.reference) { increment(); }

  // move
  refptr(refptr<T>&& ptr) : reference(ptr.reference) { ptr.reference = nullptr; }

  //destructor
  ~refptr() { decrement(); }

  T* operator->() { return get(); }
  T& operator*() { return *get(); }
  const T* operator->() const { return get(); }
  const T& operator*() const { return *get(); }

  refptr<T>& operator=(const refptr<T>&) = delete;
  const refptr<T>& operator=(const refptr<T>&) const = delete;
};

}  // namespace ros
