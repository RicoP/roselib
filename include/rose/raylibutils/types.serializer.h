#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN
//  command:
//    rose.parser -I types.h -O types.serializer.h
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  predef struct Color
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Color &lhs, const Color &rhs);
inline bool operator==(const Color &lhs, const Color &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Color &lhs, const Color &rhs) { return !equals(lhs, rhs); }
inline hash_value hash(const Color &o);

template <>
struct type_id<Color>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Color>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct Vector2
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Vector2 &lhs, const Vector2 &rhs);
inline bool operator==(const Vector2 &lhs, const Vector2 &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Vector2 &lhs, const Vector2 &rhs) { return !equals(lhs, rhs); }
inline hash_value hash(const Vector2 &o);

template <>
struct type_id<Vector2>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Vector2>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct Vector3
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Vector3 &lhs, const Vector3 &rhs);
inline bool operator==(const Vector3 &lhs, const Vector3 &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Vector3 &lhs, const Vector3 &rhs) { return !equals(lhs, rhs); }
inline hash_value hash(const Vector3 &o);

template <>
struct type_id<Vector3>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Vector3>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct Vector4
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Vector4 &lhs, const Vector4 &rhs);
inline bool operator==(const Vector4 &lhs, const Vector4 &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Vector4 &lhs, const Vector4 &rhs) { return !equals(lhs, rhs); }
inline hash_value hash(const Vector4 &o);

template <>
struct type_id<Vector4>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Vector4>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct Matrix
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Matrix &lhs, const Matrix &rhs);
inline bool operator==(const Matrix &lhs, const Matrix &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Matrix &lhs, const Matrix &rhs) { return !equals(lhs, rhs); }
inline hash_value hash(const Matrix &o);

template <>
struct type_id<Matrix>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Matrix>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct Camera3D
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Camera3D &lhs, const Camera3D &rhs);
inline bool operator==(const Camera3D &lhs, const Camera3D &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Camera3D &lhs, const Camera3D &rhs) { return !equals(lhs, rhs); }
inline void serialize(Camera3D &o, ISerializer &s);
inline void deserialize(Camera3D &o, IDeserializer &s);
inline hash_value hash(const Camera3D &o);

template <>
struct type_id<Camera3D>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Camera3D>();
} //namespace rose



#ifndef IMPL_SERIALIZER_UTIL
#define IMPL_SERIALIZER_UTIL

///////////////////////////////////////////////////////////////////
// internal helper methods
///////////////////////////////////////////////////////////////////

namespace rose {
template<class T>
bool rose_parser_equals(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

template<class T, size_t N>
bool rose_parser_equals(const T(&lhs)[N], const T(&rhs)[N]) {
  for (size_t i = 0; i != N; ++i) {
    if (!rose_parser_equals(lhs, rhs)) return false;
  }
  return true;
}

template<size_t N>
bool rose_parser_equals(const char(&lhs)[N], const char(&rhs)[N]) {
  for (size_t i = 0; i != N; ++i) {
    if (lhs[i] != rhs[i]) return false;
    if (lhs[i] == 0) return true;
  }
  return true;
}

template<class T>
bool rose_parser_equals(const std::vector<T> &lhs, const std::vector<T> &rhs) {
  if (lhs.size() != rhs.size()) return false;
  for (size_t i = 0; i != lhs.size(); ++i) {
    if (!rose_parser_equals(lhs, rhs)) return false;
  }
  return true;
}

template<class T>
hash_value rose_parser_hash(const T & value) { return hash(value); }

template<class T>
hash_value rose_parser_hash(const std::vector<T>& v) {
  hash_value h = 0;
  for (const auto& o : v) {
    h ^= rose_parser_hash(o);
    h = xor64(h);
  }
  return h;
}

}
#endif
  
///////////////////////////////////////////////////////////////////
//  impl struct Color
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Color &lhs, const Color &rhs) {
  return
    rose::rose_parser_equals(lhs.r, rhs.r) &&
    rose::rose_parser_equals(lhs.g, rhs.g) &&
    rose::rose_parser_equals(lhs.b, rhs.b) &&
    rose::rose_parser_equals(lhs.a, rhs.a);
}

inline rose::hash_value rose::hash(const Color &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.r);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.g);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.b);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.a);
  return h;
}

template <>
struct rose::type_id<Color> {
    inline static rose::hash_value VALUE = 11375897551430744876ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Color>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Color"),
    /*           member_hash */ 11375897551430744876ULL,
    /*      memory_footprint */ sizeof(Color),
    /*      memory_alignment */ 16,
    /*                  name */ "Color",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Color(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Color*>(ptr))->~Color(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Color*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Color*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct Vector2
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Vector2 &lhs, const Vector2 &rhs) {
  return
    rose::rose_parser_equals(lhs.x, rhs.x) &&
    rose::rose_parser_equals(lhs.y, rhs.y);
}

inline rose::hash_value rose::hash(const Vector2 &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.x);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.y);
  return h;
}

template <>
struct rose::type_id<Vector2> {
    inline static rose::hash_value VALUE = 6016383611561840414ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Vector2>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Vector2"),
    /*           member_hash */ 6016383611561840414ULL,
    /*      memory_footprint */ sizeof(Vector2),
    /*      memory_alignment */ 16,
    /*                  name */ "Vector2",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Vector2(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Vector2*>(ptr))->~Vector2(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Vector2*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Vector2*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct Vector3
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Vector3 &lhs, const Vector3 &rhs) {
  return
    rose::rose_parser_equals(lhs.x, rhs.x) &&
    rose::rose_parser_equals(lhs.y, rhs.y) &&
    rose::rose_parser_equals(lhs.z, rhs.z);
}

inline rose::hash_value rose::hash(const Vector3 &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.x);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.y);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.z);
  return h;
}

template <>
struct rose::type_id<Vector3> {
    inline static rose::hash_value VALUE = 865855757241434760ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Vector3>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Vector3"),
    /*           member_hash */ 865855757241434760ULL,
    /*      memory_footprint */ sizeof(Vector3),
    /*      memory_alignment */ 16,
    /*                  name */ "Vector3",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Vector3(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Vector3*>(ptr))->~Vector3(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Vector3*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Vector3*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct Vector4
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Vector4 &lhs, const Vector4 &rhs) {
  return
    rose::rose_parser_equals(lhs.x, rhs.x) &&
    rose::rose_parser_equals(lhs.y, rhs.y) &&
    rose::rose_parser_equals(lhs.z, rhs.z) &&
    rose::rose_parser_equals(lhs.w, rhs.w);
}

inline rose::hash_value rose::hash(const Vector4 &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.x);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.y);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.z);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.w);
  return h;
}

template <>
struct rose::type_id<Vector4> {
    inline static rose::hash_value VALUE = 5281526937919724321ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Vector4>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Vector4"),
    /*           member_hash */ 5281526937919724321ULL,
    /*      memory_footprint */ sizeof(Vector4),
    /*      memory_alignment */ 16,
    /*                  name */ "Vector4",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Vector4(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Vector4*>(ptr))->~Vector4(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Vector4*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Vector4*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct Matrix
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Matrix &lhs, const Matrix &rhs) {
  return
    rose::rose_parser_equals(lhs.m0, rhs.m0) &&
    rose::rose_parser_equals(lhs.m4, rhs.m4) &&
    rose::rose_parser_equals(lhs.m8, rhs.m8) &&
    rose::rose_parser_equals(lhs.m12, rhs.m12) &&
    rose::rose_parser_equals(lhs.m1, rhs.m1) &&
    rose::rose_parser_equals(lhs.m5, rhs.m5) &&
    rose::rose_parser_equals(lhs.m9, rhs.m9) &&
    rose::rose_parser_equals(lhs.m13, rhs.m13) &&
    rose::rose_parser_equals(lhs.m2, rhs.m2) &&
    rose::rose_parser_equals(lhs.m6, rhs.m6) &&
    rose::rose_parser_equals(lhs.m10, rhs.m10) &&
    rose::rose_parser_equals(lhs.m14, rhs.m14) &&
    rose::rose_parser_equals(lhs.m3, rhs.m3) &&
    rose::rose_parser_equals(lhs.m7, rhs.m7) &&
    rose::rose_parser_equals(lhs.m11, rhs.m11) &&
    rose::rose_parser_equals(lhs.m15, rhs.m15);
}

inline rose::hash_value rose::hash(const Matrix &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.m0);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m4);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m8);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m12);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m1);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m5);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m9);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m13);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m2);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m6);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m10);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m14);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m3);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m7);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m11);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.m15);
  return h;
}

template <>
struct rose::type_id<Matrix> {
    inline static rose::hash_value VALUE = 17183949275312155998ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Matrix>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Matrix"),
    /*           member_hash */ 17183949275312155998ULL,
    /*      memory_footprint */ sizeof(Matrix),
    /*      memory_alignment */ 16,
    /*                  name */ "Matrix",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Matrix(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Matrix*>(ptr))->~Matrix(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Matrix*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Matrix*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct Camera3D
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Camera3D &lhs, const Camera3D &rhs) {
  return
    rose::rose_parser_equals(lhs.position, rhs.position) &&
    rose::rose_parser_equals(lhs.target, rhs.target) &&
    rose::rose_parser_equals(lhs.up, rhs.up) &&
    rose::rose_parser_equals(lhs.fovy, rhs.fovy) &&
    rose::rose_parser_equals(lhs.projection, rhs.projection);
}

inline void rose::serialize(Camera3D &o, ISerializer &s) {
  if(s.node_begin("Camera3D", hash("Camera3D"), &o)) {
    s.key("position");
    serialize(o.position, s);
    s.key("target");
    serialize(o.target, s);
    s.key("up");
    serialize(o.up, s);
    s.key("fovy");
    serialize(o.fovy, s);
    s.key("projection");
    serialize(o.projection, s);
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(Camera3D &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("position"):
        deserialize(o.position, s);
        break;
      case rose::hash("target"):
        deserialize(o.target, s);
        break;
      case rose::hash("up"):
        deserialize(o.up, s);
        break;
      case rose::hash("fovy"):
        deserialize(o.fovy, s);
        break;
      case rose::hash("projection"):
        deserialize(o.projection, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline rose::hash_value rose::hash(const Camera3D &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.position);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.target);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.up);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.fovy);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.projection);
  return h;
}

template <>
struct rose::type_id<Camera3D> {
    inline static rose::hash_value VALUE = 17592964880055371367ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Camera3D>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Camera3D"),
    /*           member_hash */ 17592964880055371367ULL,
    /*      memory_footprint */ sizeof(Camera3D),
    /*      memory_alignment */ 16,
    /*                  name */ "Camera3D",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Camera3D(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Camera3D*>(ptr))->~Camera3D(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Camera3D*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Camera3D*>(ptr)), d); }
  };
  return info;
}

