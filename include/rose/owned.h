#pragma once

namespace rose {

template <class T>
struct owned {
 private:
  T* obj;

 public:
  owned(T* obj_) : obj(obj_) {}
  owned(owned<T>&& rhs) noexcept : obj(rhs.obj) { rhs.obj = nullptr; }
  ~owned() {
    if (!obj) return;
    delete obj;
    obj = nullptr;
  }

  owned<T>& operator=(owned<T>&& rhs) noexcept {
    if (obj) {
      delete obj;
    }
    obj = rhs.obj;
    rhs.obj = nullptr;
    return *this;
  }

  owned<T>& operator=(const owned<T>& rhs) = delete;
  owned(const owned<T>&) = delete;

  bool valid() const { return obj != nullptr; }
  T& get() {
    assert(obj);
    return *obj;
  }
  const T& get() const {
    assert(obj);
    return *obj;
  }

  bool operator==(const owned<T>& rhs) const { return obj == rhs.obj; }

  T& operator*() { return get(); }
  const T& operator*() const { return get(); }

  T* operator->() { return &get(); }
  const T* operator->() const { return &get(); }

  static owned<T> null() {
    owned<T> rtn(nullptr);
    return rtn;
  }
};

}  // namespace rose
