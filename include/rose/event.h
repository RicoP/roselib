#pragma once

#include <rose/hash.h>
#include <rose/typetraits.h>

namespace rose {
// A Pointer to the current data section representing the event.
// Keep in mind that it is only valid for the lifetime of the Queue.
struct Event {
  rose::hash_value event_id;
  size_t padded_event_size;
  char *data;  // pointing on firs byte of event struct

  template <class T>
  const T *try_get() const {
    if (rose::type_id<T>::VALUE == event_id) {
      return reinterpret_cast<const T *>(data);
    }
    return nullptr;
  }
};
}  // namespace rose
