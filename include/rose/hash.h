#pragma once

//__rdtsc
#include <intrin.h>

#ifndef ROSE_NO_STL
#include <vector>
#endif

typedef unsigned long long RHash;
static_assert(sizeof(RHash) == 8);
static_assert(sizeof(RHash) == sizeof(size_t));
static_assert(sizeof(RHash) == sizeof(void *));

namespace rose {
// http://www.jstatsoft.org/article/view/v008i14/xorshift.pdf page 4
// https://en.wikipedia.org/wiki/Xorshift#xorshift*
constexpr RHash xor64(RHash h) {
  h ^= 88172645463325252ULL;  // xor with a constant so a seed of 0 will not result in a infinite loop
  h ^= h >> 12;
  h ^= h << 25;
  h ^= h >> 27;
  return h * 0x2545F4914F6CDD1DULL;
}

// https://de.wikipedia.org/wiki/FNV_(Informatik)
constexpr RHash hash_fnv(const char* string) {
  RHash MagicPrime = 0x00000100000001b3ULL;
  RHash Hash = 0xcbf29ce484222325ULL;

  for (; *string; string++) Hash = (Hash ^ *string) * MagicPrime;

  return Hash;
}

constexpr RHash hash_fnv(const char* string, const char* end) {
  RHash MagicPrime = 0x00000100000001b3ULL;
  RHash Hash = 0xcbf29ce484222325ULL;

  for (; string != end; string++) Hash = (Hash ^ *string) * MagicPrime;

  return Hash;
}

constexpr void next(RHash& h) { h = xor64(h); }

inline RHash hash_from_clock() {
  RHash h = __rdtsc();
  next(h);
  return h;
}

template <typename T>
T next_range(RHash& h, T min, T max) {
  if (max < min) return next_range(h, max, min);
  next(h);
  min += h % (max - min);
  return min;
}

template <typename T1, typename T2>
T1 next_range(RHash& h, T1 min, T2 max) {
  return next_range<T1>(h, min, (T1)max);
}

inline float nextf(RHash& h) {
  next(h);

  union {
    RHash u_x;
    float u_f;
  };

  // Manipulate the exponent and fraction of the floating point number
  // in a way, that we get a number from 1 (inlcusive) and 2 (exclusive).
  u_x = h;
  u_x &= 0x007FFFFF007FFFFF;
  u_x |= 0x3F8000003F800000;

  return u_f - 1.0f;
}

inline float nextf(RHash& h, float min, float max) {
  if (max < min) return nextf(h, max, min);
  return min + nextf(h) * (max - min);
}

inline int nexti(RHash& h) {
  next(h);

  union {
    RHash u_x;
    int u_i;
  };

  u_x = h;

  return u_i;
}

namespace internal {
  template <class T>
  inline RHash hash_simple(T value) {
    static_assert(sizeof(T) <= sizeof(RHash), "sizeof(T) can't be bigger than sizeof(RHash)");
    union {
      RHash u_h;
      T u_f;
    };
    u_h = 0;
    u_f = value;
    return u_h;
  }
}  // namespace internal

constexpr RHash hash(unsigned char v) { return v; }
constexpr RHash hash(unsigned int v) { return v; }
constexpr RHash hash(unsigned long int v) { return v; }
constexpr RHash hash(unsigned long long int v) { return v; }
constexpr RHash hash(unsigned short int v) { return v; }

constexpr RHash hash(bool v) { return v ? 1 : 0; }

inline RHash hash(signed char v) { return internal::hash_simple(v); }
inline RHash hash(int v) { return internal::hash_simple(v); }
inline RHash hash(long int v) { return internal::hash_simple(v); }
inline RHash hash(long long int v) { return internal::hash_simple(v); }
inline RHash hash(short int v) { return internal::hash_simple(v); }

inline RHash hash(double v) { return internal::hash_simple(v); }
inline RHash hash(float v) { return internal::hash_simple(v); }
// inline RHash hash(long double v) { return internal::hash_simple(v); }
inline RHash hash(wchar_t v) { return internal::hash_simple(v); }

constexpr RHash hash(char const* input) { return hash_fnv(input); }

#ifndef ROSE_NO_STL
template<class T>
constexpr RHash hash(const std::vector<T>& v) {
  RHash h = 0;
  for (auto& o : v) {
    h ^= hash(o);
    h = xor64(h);
  }
  return h;
}
#endif

}  // namespace rose
