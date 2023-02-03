#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser -I types.h -O types.serializer.h
///////////////////////////////////////////////////////////////////

namespace rose {
  hash_value         hash(const Color &o);
  template<>
  struct type_id<Color> {
    inline static hash_value VALUE = 11375897551430744876ULL;
  };
  void construct_defaults(      Color &o); // implement me
}
bool operator==(const Color &lhs, const Color &rhs);
bool operator!=(const Color &lhs, const Color &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Color>();
}

namespace rose {
  hash_value         hash(const Vector2 &o);
  template<>
  struct type_id<Vector2> {
    inline static hash_value VALUE = 6016383611561840414ULL;
  };
  void construct_defaults(      Vector2 &o); // implement me
}
bool operator==(const Vector2 &lhs, const Vector2 &rhs);
bool operator!=(const Vector2 &lhs, const Vector2 &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Vector2>();
}

namespace rose {
  hash_value         hash(const Vector3 &o);
  template<>
  struct type_id<Vector3> {
    inline static hash_value VALUE = 865855757241434760ULL;
  };
  void construct_defaults(      Vector3 &o); // implement me
}
bool operator==(const Vector3 &lhs, const Vector3 &rhs);
bool operator!=(const Vector3 &lhs, const Vector3 &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Vector3>();
}

namespace rose {
  hash_value         hash(const Vector4 &o);
  template<>
  struct type_id<Vector4> {
    inline static hash_value VALUE = 5281526937919724321ULL;
  };
  void construct_defaults(      Vector4 &o); // implement me
}
bool operator==(const Vector4 &lhs, const Vector4 &rhs);
bool operator!=(const Vector4 &lhs, const Vector4 &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Vector4>();
}

namespace rose {
  hash_value         hash(const Matrix &o);
  template<>
  struct type_id<Matrix> {
    inline static hash_value VALUE = 17183949275312155998ULL;
  };
  void construct_defaults(      Matrix &o); // implement me
}
bool operator==(const Matrix &lhs, const Matrix &rhs);
bool operator!=(const Matrix &lhs, const Matrix &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Matrix>();
}

namespace rose {
    void        serialize(Camera3D &o, ISerializer &s);
    void      deserialize(Camera3D &o, IDeserializer &s);
  hash_value         hash(const Camera3D &o);
  template<>
  struct type_id<Camera3D> {
    inline static hash_value VALUE = 17592964880055371367ULL;
  };
  void construct_defaults(      Camera3D &o); // implement me
}
bool operator==(const Camera3D &lhs, const Camera3D &rhs);
bool operator!=(const Camera3D &lhs, const Camera3D &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Camera3D>();
}

#ifdef IMPL_SERIALIZER

    #ifndef IMPL_SERIALIZER_UTIL
    #define IMPL_SERIALIZER_UTIL
    #include <cstring>

    namespace {
    //internal helper methods
    template<class T>
    bool rose_parser_equals(const T& lhs, const T& rhs) {
      return lhs == rhs;
    }

    template<class T, size_t N>
    bool rose_parser_equals(const T(&lhs)[N], const T(&rhs)[N]) {
      for (size_t i = 0; i != N; ++i) {
        if (lhs[i] != rhs[i]) return false;
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
        if (lhs[i] != rhs[i]) return false;
      }
      return true;
    }

    template<class TL, class TR>
    void assign(TL& lhs, TR&& rhs) {
      lhs = rhs;
    }

    template<class T>
    void construct_default(std::vector<T> & v) {
      c.clear();
    }
    }
    #endif
  
///////////////////////////////////////////////////////////////////
//  struct Color
///////////////////////////////////////////////////////////////////
bool operator==(const Color &lhs, const Color &rhs) {
  return
    rose_parser_equals(lhs.r, rhs.r) &&
    rose_parser_equals(lhs.g, rhs.g) &&
    rose_parser_equals(lhs.b, rhs.b) &&
    rose_parser_equals(lhs.a, rhs.a);
}

bool operator!=(const Color &lhs, const Color &rhs) {
  return !(lhs == rhs);
}

rose::hash_value rose::hash(const Color &o) {
  rose::hash_value h = rose::hash(o.r);
  h = rose::xor64(h);
  h ^= rose::hash(o.g);
  h = rose::xor64(h);
  h ^= rose::hash(o.b);
  h = rose::xor64(h);
  h ^= rose::hash(o.a);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Color>() {
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
}

///////////////////////////////////////////////////////////////////
//  struct Vector2
///////////////////////////////////////////////////////////////////
bool operator==(const Vector2 &lhs, const Vector2 &rhs) {
  return
    rose_parser_equals(lhs.x, rhs.x) &&
    rose_parser_equals(lhs.y, rhs.y);
}

bool operator!=(const Vector2 &lhs, const Vector2 &rhs) {
  return !(lhs == rhs);
}

rose::hash_value rose::hash(const Vector2 &o) {
  rose::hash_value h = rose::hash(o.x);
  h = rose::xor64(h);
  h ^= rose::hash(o.y);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Vector2>() {
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
}

///////////////////////////////////////////////////////////////////
//  struct Vector3
///////////////////////////////////////////////////////////////////
bool operator==(const Vector3 &lhs, const Vector3 &rhs) {
  return
    rose_parser_equals(lhs.x, rhs.x) &&
    rose_parser_equals(lhs.y, rhs.y) &&
    rose_parser_equals(lhs.z, rhs.z);
}

bool operator!=(const Vector3 &lhs, const Vector3 &rhs) {
  return !(lhs == rhs);
}

rose::hash_value rose::hash(const Vector3 &o) {
  rose::hash_value h = rose::hash(o.x);
  h = rose::xor64(h);
  h ^= rose::hash(o.y);
  h = rose::xor64(h);
  h ^= rose::hash(o.z);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Vector3>() {
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
}

///////////////////////////////////////////////////////////////////
//  struct Vector4
///////////////////////////////////////////////////////////////////
bool operator==(const Vector4 &lhs, const Vector4 &rhs) {
  return
    rose_parser_equals(lhs.x, rhs.x) &&
    rose_parser_equals(lhs.y, rhs.y) &&
    rose_parser_equals(lhs.z, rhs.z) &&
    rose_parser_equals(lhs.w, rhs.w);
}

bool operator!=(const Vector4 &lhs, const Vector4 &rhs) {
  return !(lhs == rhs);
}

rose::hash_value rose::hash(const Vector4 &o) {
  rose::hash_value h = rose::hash(o.x);
  h = rose::xor64(h);
  h ^= rose::hash(o.y);
  h = rose::xor64(h);
  h ^= rose::hash(o.z);
  h = rose::xor64(h);
  h ^= rose::hash(o.w);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Vector4>() {
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
}

///////////////////////////////////////////////////////////////////
//  struct Matrix
///////////////////////////////////////////////////////////////////
bool operator==(const Matrix &lhs, const Matrix &rhs) {
  return
    rose_parser_equals(lhs.m0, rhs.m0) &&
    rose_parser_equals(lhs.m4, rhs.m4) &&
    rose_parser_equals(lhs.m8, rhs.m8) &&
    rose_parser_equals(lhs.m12, rhs.m12) &&
    rose_parser_equals(lhs.m1, rhs.m1) &&
    rose_parser_equals(lhs.m5, rhs.m5) &&
    rose_parser_equals(lhs.m9, rhs.m9) &&
    rose_parser_equals(lhs.m13, rhs.m13) &&
    rose_parser_equals(lhs.m2, rhs.m2) &&
    rose_parser_equals(lhs.m6, rhs.m6) &&
    rose_parser_equals(lhs.m10, rhs.m10) &&
    rose_parser_equals(lhs.m14, rhs.m14) &&
    rose_parser_equals(lhs.m3, rhs.m3) &&
    rose_parser_equals(lhs.m7, rhs.m7) &&
    rose_parser_equals(lhs.m11, rhs.m11) &&
    rose_parser_equals(lhs.m15, rhs.m15);
}

bool operator!=(const Matrix &lhs, const Matrix &rhs) {
  return !(lhs == rhs);
}

rose::hash_value rose::hash(const Matrix &o) {
  rose::hash_value h = rose::hash(o.m0);
  h = rose::xor64(h);
  h ^= rose::hash(o.m4);
  h = rose::xor64(h);
  h ^= rose::hash(o.m8);
  h = rose::xor64(h);
  h ^= rose::hash(o.m12);
  h = rose::xor64(h);
  h ^= rose::hash(o.m1);
  h = rose::xor64(h);
  h ^= rose::hash(o.m5);
  h = rose::xor64(h);
  h ^= rose::hash(o.m9);
  h = rose::xor64(h);
  h ^= rose::hash(o.m13);
  h = rose::xor64(h);
  h ^= rose::hash(o.m2);
  h = rose::xor64(h);
  h ^= rose::hash(o.m6);
  h = rose::xor64(h);
  h ^= rose::hash(o.m10);
  h = rose::xor64(h);
  h ^= rose::hash(o.m14);
  h = rose::xor64(h);
  h ^= rose::hash(o.m3);
  h = rose::xor64(h);
  h ^= rose::hash(o.m7);
  h = rose::xor64(h);
  h ^= rose::hash(o.m11);
  h = rose::xor64(h);
  h ^= rose::hash(o.m15);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Matrix>() {
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
}

///////////////////////////////////////////////////////////////////
//  struct Camera3D
///////////////////////////////////////////////////////////////////
bool operator==(const Camera3D &lhs, const Camera3D &rhs) {
  return
    rose_parser_equals(lhs.position, rhs.position) &&
    rose_parser_equals(lhs.target, rhs.target) &&
    rose_parser_equals(lhs.up, rhs.up) &&
    rose_parser_equals(lhs.fovy, rhs.fovy) &&
    rose_parser_equals(lhs.projection, rhs.projection);
}

bool operator!=(const Camera3D &lhs, const Camera3D &rhs) {
  return !(lhs == rhs);
}

void rose::serialize(Camera3D &o, ISerializer &s) {
  if(s.node_begin("Camera3D", rose::hash("Camera3D"), &o)) {
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

void rose::deserialize(Camera3D &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

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

rose::hash_value rose::hash(const Camera3D &o) {
  rose::hash_value h = rose::hash(o.position);
  h = rose::xor64(h);
  h ^= rose::hash(o.target);
  h = rose::xor64(h);
  h ^= rose::hash(o.up);
  h = rose::xor64(h);
  h ^= rose::hash(o.fovy);
  h = rose::xor64(h);
  h ^= rose::hash(o.projection);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<Camera3D>() {
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
}


#endif
