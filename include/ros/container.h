#pragma once

#include <cstddef>

#include "assert.h"
#include "hash.h"

#ifdef ROS_USE_EA
#  define ROSE_CONTAINER_STD eastl
#else
#  include <algorithm>
#  define ROSE_CONTAINER_STD std
#endif

namespace rose {

template <size_t MAX, class T>
struct vectorPOD {
  constexpr size_t capacity() const { return MAX; }
  void clear() { size = 0; }
  T* begin() { return elements; }
  const T* begin() const { return elements; }
  T* end() { return elements + size; }
  const T* end() const { return elements + size; }
  T* back() { return elements + size - 1; }
  const T* back() const { return elements + size - 1; }

  size_t size;
  T elements[MAX];

  T& emplace_back() {
    ROSE_ASSERT(size != capacity());
    T& ret = elements[size++];
    std::memset(&ret, 0, sizeof(T));
    new (&ret) T();
    return ret;
  }

  void erase_at(ptrdiff_t i) {
    ROSE_ASSERT(i >= 0 && i < size);
    ROSE_ASSERT(size != 0);
    --size;
    elements[i] = elements[size];
  }

  void erase(T* it) {
    ROSE_ASSERT(it);
    erase_at(it - begin());
  }

  T& operator[](size_t i) {
    ROSE_ASSERT(i >= 0 && i < size);
    return elements[i];
  }

  const T& operator[](size_t i) const {
    ROSE_ASSERT(i >= 0 && i < size);
    return elements[i];
  }
};

template <size_t MAX, class T>
struct vector : vectorPOD<MAX, T> {
  vector() : size(0) {}
};

template <class TKey, class TValue>
struct CKeyValuePair {
  TKey key;
  TValue value;
};

template <class T>
struct RoseHasher {
  constexpr ros::hash_value operator()(const T& val) const { return ros::hash(val); }
};

// This Hashmap assumes all hashes are unique. There must be a overload
// of ros::hash for the key type. Never store a pointer to a value in hashmap
// because the values will be reordered when new key-value pair is inserted.
template <size_t MAX, class TKey, class TValue, class hasher = RoseHasher<TKey>>
struct CHashmapPOD {
  typedef CKeyValuePair<ros::hash_value, TValue> KVP;

  vectorPOD<MAX, KVP> map;

  constexpr size_t capacity() const { return MAX; }
  KVP* begin() { return map.begin(); }
  const KVP* begin() const { return map.begin(); }
  KVP* end() { return map.end(); }
  const KVP* end() const { return map.end(); }
  void clear() { map.clear(); }

  auto hashing(const TKey & value) { return hasher()(value); }

  class search_comparator {
   public:
    bool operator()(const KVP& a, const ros::hash_value& b) const { return a.key < b; }
    bool operator()(const ros::hash_value& a, const KVP& b) const { return a < b.key; }
  };

  KVP* binary_search(ros::hash_value hash) { return ROSE_CONTAINER_STD::lower_bound(map.begin(), map.end(), hash, search_comparator()); }

  KVP& emplace_back(const TKey& key, const TValue& value) {
    return emplace_back(hashing(key), value);
  }

  KVP& emplace_back(ros::hash_value hash, const TValue& value) {
    auto kvpi = binary_search(hash);
    // when kvp points to first element that is bigger, so we must shift
    // all other elements back one element so we can fit in new KVP.
    // When kvp points at last element behind the array we want to insert new element at end anyway.
    ROSE_ASSERT(map.size != map.capacity());
    ROSE_ASSERT(kvpi == map.end() || kvpi->key != hash);  // we assume key is new.

    map.size++;  // increase size with initialize value;
    for (auto it = map.back(); it != kvpi; --it) {
      *it = *(it - 1);
    }
    kvpi->key = hash;
    kvpi->value = value;
    return *kvpi;
  }

  bool contains(const TKey& key) {
    auto kvp = binary_search(hashing(key));
    return kvp != map.end() && kvp->key == key;
  }

  TValue& getOrMemset0(const TKey& key) {
    TValue defaultValue;
    std::memset(&defaultValue, 0, sizeof(TValue));
    return getOrDefault(key, defaultValue);
  }

  TValue& getOrDefault(const TKey& key, const TValue& defaultValue) {
    ros::hash_value hash = hashing(key);
    auto kvpi = binary_search(hash);
    if (kvpi == map.end() || kvpi->key != hash) {
      return emplace_back(key, defaultValue).value;
    }
    return kvpi->value;
  }

  TValue& operator[](const TKey& key) { return operator[](hashing(key)); }

  TValue& operator[](ros::hash_value hash) {
    auto kvpi = binary_search(hash);
    ROSE_ASSERT(kvpi != map.end() && kvpi->key == hash);
    // C++ behaviour
    // if (kvpi == map.end() || kvpi->key != hashing(key)) {
    //  return emplace_back(key, TValue()).value;
    // }
    return kvpi->value;
  }

  const TValue& operator[](const TKey& key) const { return operator[](hashing(key)); }

  const TValue& operator[](ros::hash_value hash) const {
    auto kvpi = binary_search(hash);
    ROSE_ASSERT(kvpi != map.end() && kvpi->key == hash);
    return kvpi->value;
  }
};

template <size_t MAX, class TKey, class TValue>
struct CHashmap : CHashmapPOD<MAX, TKey, TValue> {
  CHashmap() { map.size = 0; }
};
}  // namespace rose
