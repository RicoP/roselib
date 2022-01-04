#pragma once

#include <cassert>
#include <cstring>
#include <rose/hash.h>

namespace rose {
// A Pointer to the current data section representing the event.
// Keep in mind that it is only valid for the lifetime of the Queue.
struct Event {
  rose::hash_value event_id;
  size_t padded_event_size;
  char *data;
  char *end;

  static Event from_data(char *data, char *end) {
    Event event;
    event.data = data;
    event.end = end;
    event.event_id = *reinterpret_cast<rose::hash_value *>(event.data);
    event.data += sizeof(rose::hash_value);
    event.padded_event_size = *reinterpret_cast<size_t *>(event.data);
    event.data += sizeof(size_t);
    return event;
  }

  bool has_next() const { return data + padded_event_size != end; }

  Event next() const {
    assert(has_next());
    return from_data(data + padded_event_size, end);
  }
};

template <size_t MAX>
struct EventQueue {
  union {
    //the structure of an Event block is like that
    // | ID         : 8 Byte (rose::hash_value)
    // | Size       : 8 Byte (size_t) (PADDED size of T)
    // | Event Data : X Byte (T)
    // | Padding    : 0..7 Byte (Padding so sizeof(T) is multible if 8 (sizeof(void*))
    char data[MAX];
    const void *data_allign;
  };

  size_t data_size = 0;

  size_t round_next_alligned(size_t size) {
    size_t padding = size % sizeof(void *);
    padding = sizeof(void *) - padding;
    padding = padding % sizeof(void *);
    return size + padding;
  }

  bool push_back(void *event_data, size_t event_data_size, rose::hash_value event_id) {
    size_t padded_event_data_size = round_next_alligned(event_data_size);
    size_t whole_event_size = sizeof(rose::hash_value) + sizeof(size_t) + padded_event_data_size;
    if (MAX < data_size + whole_event_size) return false;

    assert(data_size == round_next_alligned(data_size));

    std::memcpy(data + data_size, &event_id, sizeof(rose::hash_value));
    data_size += sizeof(rose::hash_value);

    std::memcpy(data + data_size, &padded_event_data_size, sizeof(size_t));
    data_size += sizeof(size_t);

    std::memcpy(data + data_size, event_data, event_data_size);
    data_size += padded_event_data_size;

    assert(data_size == round_next_alligned(data_size));
  }

  template<class T>
  bool push_back(T &event) {
    return push_back(&event, sizeof(T), rose::type_id<T>::VALUE);
  }

  //get the first event in the queue
  Event iterate() {
    return Event::from_data(data, end);
  }
};
}  // namespace rose
