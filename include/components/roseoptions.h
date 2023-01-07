///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>

#include <components/vector2.h>
#include <components/vector2.h>
namespace rose {
namespace ecs {
struct RoseOptions {
  bool raytracer;
  bool rendering;
  vector2 window_position;
  vector2 window_size;

  bool equals(const RoseOptions & rhs) const {
    return
      raytracer == rhs.raytracer &&
      rendering == rhs.rendering &&
      window_position == rhs.window_position &&
      window_size == rhs.window_size;
  }
};

inline void construct_defaults(RoseOptions & o) {
  std::memset(&o, 0, sizeof(RoseOptions));
  o.raytracer = true;
  o.rendering = true;
  o.window_position = ::vector(0,0);
  o.window_size = ::vector(640,480);
}

inline bool operator==(const RoseOptions &lhs, const RoseOptions &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const RoseOptions &lhs, const RoseOptions &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(RoseOptions &o, ISerializer &s) {
  if(s.node_begin("RoseOptions", rose::hash("RoseOptions"), &o)) {
    s.key("raytracer");
    serialize(o.raytracer, s);
    s.key("rendering");
    serialize(o.rendering, s);
    s.key("window_position");
    serialize(o.window_position, s);
    s.key("window_size");
    serialize(o.window_size, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(RoseOptions &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("raytracer"):
        deserialize(o.raytracer, s);
        break;
      case rose::hash("rendering"):
        deserialize(o.rendering, s);
        break;
      case rose::hash("window_position"):
        deserialize(o.window_position, s);
        break;
      case rose::hash("window_size"):
        deserialize(o.window_size, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(RoseOptions &o, rose::hash_value & h) {
  randomize(o.raytracer, h);
  randomize(o.rendering, h);
  randomize(o.window_position, h);
  randomize(o.window_size, h);
}
} //namespace ecs

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(const ecs::RoseOptions &o) {
    hash_value h = hash(o.raytracer);
    h = xor64(h);
    h ^= hash(o.rendering);
    h = xor64(h);
    h ^= hash(o.window_position);
    h = xor64(h);
    h ^= hash(o.window_size);
    return h;
  }
} //namespace rose
