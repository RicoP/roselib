#pragma once

#include <rose/event.h>
#include <rose/hash.h>
#include <rose/nocopy.h>
#include <rose/typetraits.h>
#include <rose/singleton.h>

#include <cassert>
#include <cstring>

namespace rose {

struct EventQueueContainerMetaInfo {
  RHash event_id;
  std::size_t alligned_size;
};

struct EventIterator {
  Event current;
  size_t meta_index;
  EventQueueContainerMetaInfo *meta;
  unsigned char *end;

  void next() {
    assert(current.data != end);
    meta_index++;
    Event new_current;
    new_current.data = ((char*)current.data) + current.padded_event_size;
    if (new_current.data == end) {
      new_current.event_id = 0;
      new_current.padded_event_size = 0;
    } else {
      new_current.event_id = meta[meta_index].event_id;
      new_current.padded_event_size = meta[meta_index].alligned_size;
    }
    current = new_current;
  }

  // Compare operators actually just check for the data pointer.
  bool operator==(const EventIterator &rhs) { return current.data == rhs.current.data; }
  bool operator!=(const EventIterator &rhs) { return current.data != rhs.current.data; }
  Event operator*() { return current; }
  EventIterator &operator++() {
    next();
    return *this;
  }
};

template <size_t MAX_SIZE, size_t MAX_ELEMENTS>
struct alignas(32) EventQueueContainer {
  // The structure of an Event block is like that
  // | Event Data : X Byte (T)
  // | Padding    : 0..7 Byte (Padding so sizeof(T) is multible if 8 == sizeof(void*)
  // This must be the first member or else the allignment will be off.
  unsigned char data[MAX_SIZE];
  EventQueueContainerMetaInfo meta[MAX_ELEMENTS];
  size_t data_size = 0;
  size_t meta_size = 0;
};

struct EventQueue : RoseSingleton<EventQueue> {
  unsigned char *data;
  EventQueueContainerMetaInfo *meta;
  size_t *data_size;
  size_t *meta_size;
  size_t max_data_size;
  size_t max_meta_size;

  EventQueue() = delete;

  template <size_t MAX_DATA, size_t MAX_META>
  EventQueue(EventQueueContainer<MAX_DATA, MAX_META> &container)
      : data(container.data), meta(container.meta), data_size(&container.data_size), meta_size(&container.meta_size), max_data_size(MAX_DATA), max_meta_size(MAX_META) {}

  static size_t round_next_alligned(size_t size) {
    size_t padding = size % 32;
    padding = 32 - padding;
    padding = padding % 32;
    return size + padding;
  }

  void clear() { *data_size = *meta_size = 0; }

  // thanks leo at #inlcude
  // https://discord.com/channels/400588936151433218/469633149308239873/928747919870423050

  template <class T>
  void push_back(T &event) {
    auto event_id = rose::type_id<T>::VALUE;
    size_t padded_event_data_size = round_next_alligned(sizeof(T));

    assert(max_data_size >= *data_size + padded_event_data_size);

    assert(*data_size == round_next_alligned(*data_size));

    ::new (data + *data_size) T(event);
    *data_size += padded_event_data_size;

    assert(*meta_size != max_meta_size);

    meta[*meta_size].event_id = event_id;
    meta[*meta_size].alligned_size = padded_event_data_size;
    (*meta_size)++;

    assert(*data_size == round_next_alligned(*data_size));
  }

  // get the first event in the queue
  EventIterator begin() {
    Event current;
    current.padded_event_size = meta[0].alligned_size;
    current.event_id = meta[0].event_id;
    current.data = data;

    EventIterator i;
    i.meta_index = 0;
    i.meta = meta;
    i.current = current;
    i.end = data + *data_size;
    return i;
  }

  EventIterator end() {
    Event current;
    current.padded_event_size = 0;
    current.event_id = 0;
    current.data = data + *data_size;

    EventIterator i;
    i.meta_index = *meta_size;
    i.meta = meta;
    i.current = current;
    i.end = data + *data_size;
    return i;
  }

  size_t count() { return *meta_size; }
};
}  // namespace rose
