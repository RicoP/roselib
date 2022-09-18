#pragma once

#include <cassert>

namespace rose {

template <class T>
struct owned {
 private:
  T* obj;

 public:
  owned(T* obj_) noexcept /* implicit */ : obj(obj_) {}
  owned() noexcept : obj(nullptr) {}
  owned(owned<T>&& rhs) noexcept : obj(rhs.obj) { rhs.obj = nullptr; }
  owned(const owned<T>&) = delete;

  owned<T>& operator=(const owned<T>& rhs) = delete;
  owned<T>& operator=(owned<T>&& rhs) noexcept {
    if (obj) {
      delete obj;
    }
    obj = rhs.obj;
    rhs.obj = nullptr;
    return *this;
  }

  ~owned() {
    if (!obj) return;
    delete obj;
    obj = nullptr;
  }

  T& get() {
    assert(obj);
    return *obj;
  }
  const T& get() const {
    assert(obj);
    return *obj;
  }

  bool operator==(const owned<T>& rhs) const { return obj == rhs.obj; }
  bool operator==(const T* rhs) const { return obj == rhs; }
  bool operator!=(const owned<T>& rhs) const { return obj != rhs.obj; }
  bool operator!=(const T* rhs) const { return obj != rhs; }

  T& operator*() { return get(); }
  const T& operator*() const { return get(); }

  T* operator->() { return obj; }
  const T* operator->() const { return obj; }

  bool valid() const { return obj != nullptr; }

  void destroy() {
    if (!obj) return;
    delete obj;
    obj = nullptr;
  }
};

}  // namespace rose
