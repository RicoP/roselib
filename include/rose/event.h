#pragma once

#include <rose/hash.h>
#include <rose/typetraits.h>

namespace rose {
// A Pointer to the current data section representing the event.
// Keep in mind that it is only valid for the lifetime of the Queue.
struct Event {
  rose::hash_value event_id = 0;
  size_t padded_event_size = 0;
  char *data = nullptr;  // pointing on first byte of event struct

  template <class T>
  const T *get() const {
    if (rose::type_id<T>::VALUE == event_id) {
      return reinterpret_cast<const T *>(data);
    }
    return nullptr;
  }

  template <class T>
  T *get_mutable() {
    if (rose::type_id<T>::VALUE == event_id) {
      return reinterpret_cast<T *>(data);
    }
    return nullptr;
  }
};
}  // namespace rose
