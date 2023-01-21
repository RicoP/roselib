#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser -I .\engine\recording.h -O .\engine\recording.serializer.hpp
///////////////////////////////////////////////////////////////////

enum class                   RoseRecordingState : int ;
const char * to_string(const RoseRecordingState &);
namespace rose {
  namespace ecs {
    void      deserialize(RoseRecordingState &o, IDeserializer &s);
    void        serialize(RoseRecordingState &o, ISerializer &s);
  }
  template<>
  struct type_id<RoseRecordingState> {
    inline static hash_value VALUE = 17245467189916409023ULL;
  };
  hash_value         hash(const RoseRecordingState &o);
  void construct_defaults(      RoseRecordingState &o); //implement me
}

inline BoolConvertible<RoseRecordingState, int > operator|(const RoseRecordingState &a, const RoseRecordingState &b) { return { static_cast<RoseRecordingState>(static_cast<int >(a) | static_cast<int >(b)) }; }
inline BoolConvertible<RoseRecordingState, int > operator&(const RoseRecordingState &a, const RoseRecordingState &b) { return { static_cast<RoseRecordingState>(static_cast<int >(a) & static_cast<int >(b)) }; }
inline BoolConvertible<RoseRecordingState, int > operator^(const RoseRecordingState &a, const RoseRecordingState &b) { return { static_cast<RoseRecordingState>(static_cast<int >(a) ^ static_cast<int >(b)) }; }
inline RoseRecordingState operator|=(RoseRecordingState &a, RoseRecordingState b) { return a = a | b; }
inline RoseRecordingState operator&=(RoseRecordingState &a, RoseRecordingState b) { return a = a & b; }
inline RoseRecordingState operator^=(RoseRecordingState &a, RoseRecordingState b) { return a = a ^ b; }


struct                RoseRecordingRequest;
namespace rose {
  namespace ecs {
    void        serialize(RoseRecordingRequest &o, ISerializer &s);
    void      deserialize(RoseRecordingRequest &o, IDeserializer &s);
  }
  hash_value         hash(const RoseRecordingRequest &o);
  template<>
  struct type_id<RoseRecordingRequest> {
    inline static hash_value VALUE = 971013233248560044ULL;
  };
  void construct_defaults(      RoseRecordingRequest &o); // implement me
}
bool operator==(const RoseRecordingRequest &lhs, const RoseRecordingRequest &rhs);
bool operator!=(const RoseRecordingRequest &lhs, const RoseRecordingRequest &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<RoseRecordingRequest>();
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
  
const char * to_string(const RoseRecordingState & e) {
    switch(e) {
        case RoseRecordingState::NONE: return "NONE";
        case RoseRecordingState::RecordingStart: return "RecordingStart";
        case RoseRecordingState::Recording: return "Recording";
        case RoseRecordingState::RecordingStop: return "RecordingStop";
        case RoseRecordingState::RecordingMask: return "RecordingMask";
        case RoseRecordingState::ReplayingStart: return "ReplayingStart";
        case RoseRecordingState::Replaying: return "Replaying";
        case RoseRecordingState::ReplayingSeek: return "ReplayingSeek";
        case RoseRecordingState::ReplayingStop: return "ReplayingStop";
        case RoseRecordingState::ReplayingMask: return "ReplayingMask";
        case RoseRecordingState::Inactive: return "Inactive";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(RoseRecordingState& o, ISerializer& s) {
  switch (o) {
    case RoseRecordingState::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::RecordingStart: {
      char str[] = "RecordingStart";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::Recording: {
      char str[] = "Recording";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::RecordingStop: {
      char str[] = "RecordingStop";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::RecordingMask: {
      char str[] = "RecordingMask";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::ReplayingStart: {
      char str[] = "ReplayingStart";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::Replaying: {
      char str[] = "Replaying";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::ReplayingSeek: {
      char str[] = "ReplayingSeek";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::ReplayingStop: {
      char str[] = "ReplayingStop";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::ReplayingMask: {
      char str[] = "ReplayingMask";
      serialize(str, s);
      break;
    }
    case RoseRecordingState::Inactive: {
      char str[] = "Inactive";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(RoseRecordingState& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = RoseRecordingState::NONE; break;
  case rose::hash("RecordingStart"): o = RoseRecordingState::RecordingStart; break;
  case rose::hash("Recording"): o = RoseRecordingState::Recording; break;
  case rose::hash("RecordingStop"): o = RoseRecordingState::RecordingStop; break;
  case rose::hash("RecordingMask"): o = RoseRecordingState::RecordingMask; break;
  case rose::hash("ReplayingStart"): o = RoseRecordingState::ReplayingStart; break;
  case rose::hash("Replaying"): o = RoseRecordingState::Replaying; break;
  case rose::hash("ReplayingSeek"): o = RoseRecordingState::ReplayingSeek; break;
  case rose::hash("ReplayingStop"): o = RoseRecordingState::ReplayingStop; break;
  case rose::hash("ReplayingMask"): o = RoseRecordingState::ReplayingMask; break;
  case rose::hash("Inactive"): o = RoseRecordingState::Inactive; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const RoseRecordingState& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  struct RoseRecordingRequest
///////////////////////////////////////////////////////////////////
bool operator==(const RoseRecordingRequest &lhs, const RoseRecordingRequest &rhs) {
  return
    rose_parser_equals(lhs.state, rhs.state) &&
    rose_parser_equals(lhs.seek, rhs.seek) ;
}

bool operator!=(const RoseRecordingRequest &lhs, const RoseRecordingRequest &rhs) {
  return
    !rose_parser_equals(lhs.state, rhs.state) ||
    !rose_parser_equals(lhs.seek, rhs.seek) ;
}

void rose::ecs::serialize(RoseRecordingRequest &o, ISerializer &s) {
  if(s.node_begin("RoseRecordingRequest", rose::hash("RoseRecordingRequest"), &o)) {
    s.key("state");
    serialize(o.state, s);
    s.key("seek");
    serialize(o.seek, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(RoseRecordingRequest &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("state"):
        deserialize(o.state, s);
        break;
      case rose::hash("seek"):
        deserialize(o.seek, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const RoseRecordingRequest &o) {
  rose::hash_value h = rose::hash(o.state);
  h = rose::xor64(h);
  h ^= rose::hash(o.seek);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<RoseRecordingRequest>() {
    static rose::reflection::TypeInfo info = {
      /*             unique_id */ rose::hash("RoseRecordingRequest"),
      /*           member_hash */ 971013233248560044ULL,
      /*      memory_footprint */ sizeof(RoseRecordingRequest),
      /*      memory_alignment */ 16,
      /*                  name */ "RoseRecordingRequest",
      /*  fp_default_construct */ +[](void * ptr) { new (ptr) RoseRecordingRequest(); },
      /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<RoseRecordingRequest*>(ptr))->~RoseRecordingRequest(); },
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<RoseRecordingRequest*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<RoseRecordingRequest*>(ptr)), d); }
    };
    return info;
  }
}


#endif
