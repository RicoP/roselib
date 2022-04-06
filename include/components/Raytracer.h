///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>

#include <components/shaderassetref.h>
#include <components/shaderassetref.h>
namespace rose {
namespace ecs {
struct Raytracer {
  ShaderAssetRef fragment;
  ShaderAssetRef vertex;

  bool equals(const Raytracer & rhs) const {
    return
      fragment == rhs.fragment &&
      vertex == rhs.vertex;
  }
};

inline void construct_defaults(Raytracer & o) {
  std::memset(&o, 0, sizeof(Raytracer));
  construct_defaults(o.fragment);
  construct_defaults(o.vertex);
}

inline bool operator==(const Raytracer &lhs, const Raytracer &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const Raytracer &lhs, const Raytracer &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(Raytracer &o, ISerializer &s) {
  if(s.node_begin("Raytracer", rose::hash("Raytracer"), &o)) {
    s.key("fragment");
    serialize(o.fragment, s);
    s.key("vertex");
    serialize(o.vertex, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(Raytracer &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("fragment"):
        deserialize(o.fragment, s);
        break;
      case rose::hash("vertex"):
        deserialize(o.vertex, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(Raytracer &o, rose::hash_value & h) {
  randomize(o.fragment, h);
  randomize(o.vertex, h);
}
} //namespace ecs

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(const ecs::Raytracer &o) {
    hash_value h = hash(o.fragment);
    h = xor64(h);
    h ^= hash(o.vertex);
    return h;
  }
} //namespace rose