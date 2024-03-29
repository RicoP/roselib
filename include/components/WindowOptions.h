///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <cstring>

namespace rose {
struct WindowOptions {
  bool popped;

  bool equals(const WindowOptions & rhs) const {
    return
      popped == rhs.popped;
  }
};

inline void construct_defaults(WindowOptions & o) {
  std::memset(&o, 0, sizeof(WindowOptions));
}

inline bool operator==(const WindowOptions &lhs, const WindowOptions &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const WindowOptions &lhs, const WindowOptions &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(WindowOptions &o, ISerializer &s) {
  if(s.node_begin("WindowOptions", rose::hash("WindowOptions"), &o)) {
    s.key("popped");
    serialize(o.popped, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(WindowOptions &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("popped"):
        deserialize(o.popped, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(WindowOptions &o, RHash & h) {
  randomize(o.popped, h);
}

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline RHash hash(const WindowOptions &o) {
    RHash h = hash(o.popped);
    return h;
  }
} //namespace rose
