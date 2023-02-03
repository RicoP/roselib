///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <cstring>

#include <components/vector3.h>
#include <components/vector3.h>
#include <components/camera.h>
#include <components/cubehero.h>
namespace rose {
struct CubeWorld {
  vector3 cam_position;
  vector3 cam_up;
  Camera camera;
  Cubehero hero;
  int max_cubes;
  rose::hash_value seed;

  bool equals(const CubeWorld & rhs) const {
    return
      cam_position == rhs.cam_position &&
      cam_up == rhs.cam_up &&
      camera == rhs.camera &&
      hero == rhs.hero &&
      max_cubes == rhs.max_cubes &&
      seed == rhs.seed;
  }
};

inline void construct_defaults(CubeWorld & o) {
  std::memset(&o, 0, sizeof(CubeWorld));
  o.cam_position = ::vector(0, 0, 10);
  o.cam_up = ::vector(0, 1, 0);
  construct_defaults(o.camera);
  construct_defaults(o.hero);
  o.max_cubes = 16;
}

inline bool operator==(const CubeWorld &lhs, const CubeWorld &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const CubeWorld &lhs, const CubeWorld &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(CubeWorld &o, ISerializer &s) {
  if(s.node_begin("CubeWorld", rose::hash("CubeWorld"), &o)) {
    s.key("cam_position");
    serialize(o.cam_position, s);
    s.key("cam_up");
    serialize(o.cam_up, s);
    s.key("camera");
    serialize(o.camera, s);
    s.key("hero");
    serialize(o.hero, s);
    s.key("max_cubes");
    serialize(o.max_cubes, s);
    s.key("seed");
    serialize(o.seed, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(CubeWorld &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("cam_position"):
        deserialize(o.cam_position, s);
        break;
      case rose::hash("cam_up"):
        deserialize(o.cam_up, s);
        break;
      case rose::hash("camera"):
        deserialize(o.camera, s);
        break;
      case rose::hash("hero"):
        deserialize(o.hero, s);
        break;
      case rose::hash("max_cubes"):
        deserialize(o.max_cubes, s);
        break;
      case rose::hash("seed"):
        deserialize(o.seed, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(CubeWorld &o, rose::hash_value & h) {
  randomize(o.cam_position, h);
  randomize(o.cam_up, h);
  randomize(o.camera, h);
  randomize(o.hero, h);
  randomize(o.max_cubes, h);
  randomize(o.seed, h);
}

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(const CubeWorld &o) {
    hash_value h = hash(o.cam_position);
    h = xor64(h);
    h ^= hash(o.cam_up);
    h = xor64(h);
    h ^= hash(o.camera);
    h = xor64(h);
    h ^= hash(o.hero);
    h = xor64(h);
    h ^= hash(o.max_cubes);
    h = xor64(h);
    h ^= hash(o.seed);
    return h;
  }
} //namespace rose
