#pragma once

#include <rose/container.h>
#include <rose/hash.h>

#include <components/guid.h>
#include <components/localdate.h>

#include <ctime>

using hash_value = rose::hash_value;

struct AssetRef {
  hash_value id;
};

inline bool operator==(const AssetRef& lhs, const AssetRef& rhs) { return lhs.id == rhs.id; }
inline void construct_defaults(AssetRef& o) { o.id = 0; }

struct SoundAssetRef : public AssetRef {};
struct TextureAssetRef : public AssetRef {};
struct MeshAssetRef : public AssetRef {};
struct ShaderAssetRef : public AssetRef {};

struct ObjectID {
  hash_value id;

  static constexpr ObjectID empty() { return ObjectID{0}; }
};

inline ObjectID idgen() { return ObjectID{rose::hash_from_clock()}; }

inline void construct_defaults(ObjectID& o) { o.id = 0; }

inline bool operator==(const ObjectID& lhs, const ObjectID& rhs) { return lhs.id == rhs.id; }
inline bool operator!=(const ObjectID& lhs, const ObjectID& rhs) { return lhs.id != rhs.id; }

constexpr rose::hash_value field_hash(const char* name, const char* type) { return rose::hash(name) ^ rose::hash(type); }

// Helper class to serialize fixed arrays
template <size_t MAX, class T>
struct CArray : rose::vector<MAX, T> {};

template <size_t MAX, class TKey, class TValue>
struct CHashmap : rose::Hashmap<MAX, TKey, TValue> {};

// Helper class to serialize fixed strings
template <size_t MAX>
struct CString {
  char s[MAX];

  constexpr size_t capacity() const { return MAX; }
};


inline rose::GUID create_guid() {
  static_assert(sizeof(hash_value) * 2 == sizeof(rose::GUID));
  union {
    hash_value h[2];
    rose::GUID guid = {{0}};
  } u;

  std::time_t rawtime = time(nullptr);
  hash_value h1 = rose::hash(rawtime);
  rose::next(h1);
  hash_value h2 = rose::hash_from_clock();

  u.h[0] = h1;
  u.h[1] = h2;

  return u.guid;
}

inline rose::LocalDate create_local_date() {

  std::time_t now = std::time(NULL);
  std::tm * t = std::localtime(&now);
  // clang-format off
  int date = (
    //        YYYYMMDDZZ
    t->tm_year * 1000000 +
    t->tm_mon  *   10000 +
    t->tm_mday *     100 +
                      00 // time zone is 0 for now
    );
  int time = (
    //          HHMMSSMMM
    t->tm_hour * 10000000 +
    t->tm_min  *   100000 +
    t->tm_sec  *     1000 +
                      000 //Miliseconds are zero for now
    );
  // clang-format on

  rose::LocalDate ld;
  ld.date = date;
  ld.time = time;
  return ld;
}
