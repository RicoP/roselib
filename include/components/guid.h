#pragma once

#include <serializer/serializer.h>
#include <components/localdate.h>
#include <components/computils.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

namespace rose {
  struct GUID {
    unsigned char data[16];

    bool equals(const GUID &rhs) const { return std::memcmp(data, rhs.data, 16) == 0; }
  };

  inline void construct_defaults(GUID &o) { std::memset(o.data, 0, 16); }

  inline bool operator==(const GUID &lhs, const GUID &rhs) { return lhs.equals(rhs); }

  inline bool operator!=(const GUID &lhs, const GUID &rhs) { return !lhs.equals(rhs); }

  inline void serialize(GUID &o, ISerializer &s) {
    rose::string<64> guid;
    unsigned char *p = o.data;
    // clang-format off
    std::sprintf(guid.data,
                 "%02X" "%02X" "%02X""%02X-"
                 "%02X" "%02X-"
                 "%02X" "%02X-"
                 "%02X" "%02X-"
                 "%02X" "%02X" "%02X" "%02X" "%02X" "%02X",
                 p[ 0], p[ 1], p[ 2], p[ 3],
                 p[ 4], p[ 5],
                 p[ 6], p[ 7],
                 p[ 8], p[ 9],
                 p[10], p[11], p[12], p[13], p[14], p[15]);
    // clang-format on
    serialize(guid, s, 36);
  }

  inline void deserialize(GUID &o, IDeserializer &s) {
    rose::string<64> guid;
    deserialize(guid, s);
    char *src = guid.data;
    unsigned char *dest = o.data;

    char hex[3] = {0, 0, 0};
    char *hexp = hex;

    for (;; ++src) {
      if (*src == '-') continue;
      if (*src == 0) break;

      *hexp = *src;
      hexp++;
      if (hexp == hex + 2) {
        hexp = hex;
        long value = strtol(hex, nullptr, 16);
        assert(dest != o.data + 16);
        *dest = (unsigned char)value;
        ++dest;
      }
    }

    assert(dest == o.data + 16);
  }

  inline void randomize(GUID &o, RHash &h) {
    static_assert(sizeof(RHash) * 2 == sizeof(GUID));
    union {
      RHash h[2];
      GUID guid = {{0}};
    } u;
    next(h);
    u.h[0] = h;
    next(h);
    u.h[1] = h;
    o = u.guid;
  }

inline RHash hash(GUID &o) {
  static_assert(sizeof(RHash) * 2 == sizeof(GUID));
  union {
    RHash h[2];
    GUID guid;
  } u;
  u.guid = o;
  return u.h[0] ^ u.h[1];
}
}  // namespace rose
