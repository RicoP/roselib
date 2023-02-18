#pragma once

#include <serializer/serializer.h>

struct Path {
  //@String
  char string[260] = "";

  Path& operator=(const char *str) { strcpy(string, str); return *this; }

  bool operator==(const char* rhs) const { return strcmp(string, rhs) == 0; }
  bool operator!=(const char* rhs) const { return !(*this == rhs); }
};

namespace rose {

inline void        serialize(Path &o, ISerializer &s) {
	rose::serialize(o.string, s);
}
inline void      deserialize(Path &o, IDeserializer &s) {
	rose::deserialize(o.string, s);
}

}
