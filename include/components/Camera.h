///////////////////////////////////////////////////////////////////
// AUTOGENERATED do not edit by hand                             //
///////////////////////////////////////////////////////////////////
#pragma once
#include <components/computils.h>
#include <serializer/serializer.h>
#include <rose/ecs.h>
#include <cstring>

#include <components/matrix4.h>
#include <components/matrix4.h>
namespace rose {
namespace ecs {
struct Camera {
  matrix4 projection;
  matrix4 lookat;
  float far_plane;
  float near_plane;
  float fov;

  bool equals(const Camera & rhs) const {
    return
      far_plane == rhs.far_plane &&
      fov == rhs.fov &&
      lookat == rhs.lookat &&
      near_plane == rhs.near_plane &&
      projection == rhs.projection;
  }
};

inline void construct_defaults(Camera & o) {
  std::memset(&o, 0, sizeof(Camera));
  o.far_plane = 1000;
  o.fov = 70;
  o.lookat = identity4();
  o.near_plane = 0.1f;
  o.projection = identity4();
}

inline bool operator==(const Camera &lhs, const Camera &rhs) {
  return lhs.equals(rhs);
}

inline bool operator!=(const Camera &lhs, const Camera &rhs) {
  return !lhs.equals(rhs);
}

///////////////////////////////////////////////////////////////////
// serializer                                                    //
///////////////////////////////////////////////////////////////////
inline void serialize(Camera &o, ISerializer &s) {
  if(s.node_begin("Camera", rose::hash("Camera"), &o)) {
    s.key("far_plane");
    serialize(o.far_plane, s);
    s.key("fov");
    serialize(o.fov, s);
    s.key("lookat");
    serialize(o.lookat, s);
    s.key("near_plane");
    serialize(o.near_plane, s);
    s.key("projection");
    serialize(o.projection, s);
    s.node_end();
  }
  s.end();
}

///////////////////////////////////////////////////////////////////
// deserializer                                                  //
///////////////////////////////////////////////////////////////////
inline void deserialize(Camera &o, IDeserializer &s) {
  construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("far_plane"):
        deserialize(o.far_plane, s);
        break;
      case rose::hash("fov"):
        deserialize(o.fov, s);
        break;
      case rose::hash("lookat"):
        deserialize(o.lookat, s);
        break;
      case rose::hash("near_plane"):
        deserialize(o.near_plane, s);
        break;
      case rose::hash("projection"):
        deserialize(o.projection, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

///////////////////////////////////////////////////////////////////
// randomize                                                     //
///////////////////////////////////////////////////////////////////
inline void randomize(Camera &o, rose::hash_value & h) {
  randomize(o.far_plane, h);
  randomize(o.fov, h);
  randomize(o.lookat, h);
  randomize(o.near_plane, h);
  randomize(o.projection, h);
}
} //namespace ecs

///////////////////////////////////////////////////////////////////
// hashing                                                       //
///////////////////////////////////////////////////////////////////
  inline hash_value hash(ecs::Camera &o) {
    hash_value h = hash(o.far_plane);
    h = xor64(h);
    h ^= hash(o.fov);
    h = xor64(h);
    h ^= hash(o.lookat);
    h = xor64(h);
    h ^= hash(o.near_plane);
    h = xor64(h);
    h ^= hash(o.projection);
    return h;
  }
} //namespace rose
