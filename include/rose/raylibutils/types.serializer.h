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
  namespace ecs {
  }
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
  namespace ecs {
  }
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
  namespace ecs {
    void        serialize(Camera3D &o, ISerializer &s);
    void      deserialize(Camera3D &o, IDeserializer &s);
  }
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
    rose_parser_equals(lhs.a, rhs.a) ;
}

bool operator!=(const Color &lhs, const Color &rhs) {
  return
    !rose_parser_equals(lhs.r, rhs.r) ||
    !rose_parser_equals(lhs.g, rhs.g) ||
    !rose_parser_equals(lhs.b, rhs.b) ||
    !rose_parser_equals(lhs.a, rhs.a) ;
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
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<Color*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<Color*>(ptr)), d); }
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
    rose_parser_equals(lhs.z, rhs.z) ;
}

bool operator!=(const Vector3 &lhs, const Vector3 &rhs) {
  return
    !rose_parser_equals(lhs.x, rhs.x) ||
    !rose_parser_equals(lhs.y, rhs.y) ||
    !rose_parser_equals(lhs.z, rhs.z) ;
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
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<Vector3*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<Vector3*>(ptr)), d); }
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
    rose_parser_equals(lhs.projection, rhs.projection) ;
}

bool operator!=(const Camera3D &lhs, const Camera3D &rhs) {
  return
    !rose_parser_equals(lhs.position, rhs.position) ||
    !rose_parser_equals(lhs.target, rhs.target) ||
    !rose_parser_equals(lhs.up, rhs.up) ||
    !rose_parser_equals(lhs.fovy, rhs.fovy) ||
    !rose_parser_equals(lhs.projection, rhs.projection) ;
}

void rose::ecs::serialize(Camera3D &o, ISerializer &s) {
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

void rose::ecs::deserialize(Camera3D &o, IDeserializer &s) {
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
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<Camera3D*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<Camera3D*>(ptr)), d); }
    };
    return info;
  }
}


#endif
