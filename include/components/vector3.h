///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>


#include <rosemath.h>

namespace rose {
namespace ecs {

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(vector3 &o, ISerializer &s) {
  if(s.node_begin("vector3", rose::hash("vector3"), &o)) {
    s.key("x");
    serialize(o.x, s);
    s.key("y");
    serialize(o.y, s);
    s.key("z");
    serialize(o.z, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(vector3 &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("x"):
        deserialize(o.x, s);
        break;
      case rose::hash("y"):
        deserialize(o.y, s);
        break;
      case rose::hash("z"):
        deserialize(o.z, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(vector3 &o, rose::hash_value & h) {
  randomize(o.x, h);
  randomize(o.y, h);
  randomize(o.z, h);
}
} //namespace ecs

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(const vector3 &o) {
    hash_value h = hash(o.x);
    h = xor64(h);
    h ^= hash(o.y);
    h = xor64(h);
    h ^= hash(o.z);
    return h;
  }
} //namespace rose
