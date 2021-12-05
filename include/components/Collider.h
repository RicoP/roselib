///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>

#include <components/objectid.h>
#include <components/vector3.h>
#include <components/vector3.h>
namespace rose {
namespace ecs {
struct Collider {
  bool active;
  rose::vectorPOD<16, ObjectID> intersections;
  vector3 pivot;
  vector3 scale;

  bool equals(const Collider & rhs) const {
    return
      active == rhs.active &&
      intersections == rhs.intersections &&
      pivot == rhs.pivot &&
      scale == rhs.scale;
  }
};

inline void construct_defaults(Collider & o) {
  std::memset(&o, 0, sizeof(Collider));
  o.intersections.size = 0;
  o.pivot = ::vector(0,0,0);
  o.scale = ::vector(1,1,1);
}

inline bool operator==(const Collider &lhs, const Collider &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const Collider &lhs, const Collider &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(Collider &o, ISerializer &s) {
  if(s.node_begin("Collider", rose::hash("Collider"), &o)) {
    s.key("active");
    serialize(o.active, s);
    s.key("intersections");
    serialize(o.intersections, s);
    s.key("pivot");
    serialize(o.pivot, s);
    s.key("scale");
    serialize(o.scale, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(Collider &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("active"):
        deserialize(o.active, s);
        break;
      case rose::hash("intersections"):
        deserialize(o.intersections, s);
        break;
      case rose::hash("pivot"):
        deserialize(o.pivot, s);
        break;
      case rose::hash("scale"):
        deserialize(o.scale, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(Collider &o, rose::hash_value & h) {
  randomize(o.active, h);
  randomize(o.intersections, h);
  randomize(o.pivot, h);
  randomize(o.scale, h);
}
} //namespace ecs

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(ecs::Collider &o) {
    hash_value h = hash(o.active);
    h = xor64(h);
    h ^= hash(o.intersections);
    h = xor64(h);
    h ^= hash(o.pivot);
    h = xor64(h);
    h ^= hash(o.scale);
    return h;
  }
} //namespace rose
