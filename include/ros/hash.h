#pragma once

#ifdef ROS_USE_EA
#  include <EAStdC/EAStopwatch.h>
#endif

namespace ros {

typedef unsigned long long hash_value;

static_assert(sizeof(hash_value) == 8 && sizeof(hash_value) == sizeof(size_t));

// http://www.jstatsoft.org/article/view/v008i14/xorshift.pdf page 4
// https://en.wikipedia.org/wiki/Xorshift#xorshift*
constexpr hash_value xor64(hash_value h) {
  h ^= 88172645463325252ULL;  // xor with a constant so a seed of 0 will not result in a infinite loop
  h ^= h >> 12;
  h ^= h << 25;
  h ^= h >> 27;
  return h * 0x2545F4914F6CDD1DULL;
}

// https://de.wikipedia.org/wiki/FNV_(Informatik)
constexpr hash_value hash_fnv(const char* string) {
  hash_value MagicPrime = 0x00000100000001b3ULL;
  hash_value Hash       = 0xcbf29ce484222325ULL;

  for (; *string; string++) Hash = (Hash ^ *string) * MagicPrime;

  return Hash;
}

constexpr void next(hash_value& h) { h = xor64(h); }

#ifdef ROS_USE_EA
inline hash_value hash_from_clock() {
  hash_value h = EA::StdC::Stopwatch::GetCPUCycle();
  next(h);
  return h;
}
#endif

constexpr hash_value next_range(hash_value& h, hash_value min, hash_value max) {
  next(h);
  hash_value r = h % (max - min);
  return r + min;
}

inline float nextf(hash_value& h) {
  next(h);

  union {
    hash_value u_x;
    float u_f;
  };

  // Manipulate the exponent and fraction of the floating point number
  // in a way, that we get a number from 1 (inlcusive) and 2 (exclusive).
  u_x = h;
  u_x &= 0x007FFFFF007FFFFF;
  u_x |= 0x3F8000003F800000;

  return u_f - 1.0f;
}

namespace internal {
  template <class T>
  inline hash_value hash_simple(T value) {
    static_assert(sizeof(T) <= sizeof(hash_value), "sizeof(T) can't be bigger than sizeof(hash_value)");
    union {
      hash_value u_h;
      T u_f;
    };
    u_h = 0;
    u_f = value;
    return u_h;
  }
}  // namespace internal

constexpr hash_value hash(unsigned char v) { return v; }
constexpr hash_value hash(unsigned int v) { return v; }
constexpr hash_value hash(unsigned long int v) { return v; }
constexpr hash_value hash(unsigned long long int v) { return v; }
constexpr hash_value hash(unsigned short int v) { return v; }

constexpr hash_value hash(bool v) { return v ? 1 : 0; }

inline hash_value hash(signed char v) { return internal::hash_simple(v); }
inline hash_value hash(int v) { return internal::hash_simple(v); }
inline hash_value hash(long int v) { return internal::hash_simple(v); }
inline hash_value hash(long long int v) { return internal::hash_simple(v); }
inline hash_value hash(short int v) { return internal::hash_simple(v); }

inline hash_value hash(double v) { return internal::hash_simple(v); }
inline hash_value hash(float v) { return internal::hash_simple(v); }
inline hash_value hash(long double v) { return internal::hash_simple(v); }
inline hash_value hash(wchar_t v) { return internal::hash_simple(v); }

constexpr hash_value hash(char const* input, hash_value seed = 0) { return *input == 0 ? seed : (*input) ^ xor64(hash(input + 1, seed)); }

}  // namespace ros
