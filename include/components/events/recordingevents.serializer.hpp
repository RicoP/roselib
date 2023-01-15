#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser -I .\events\recordingevents.h -O .\events\recordingevents.serializer.hpp
///////////////////////////////////////////////////////////////////

enum class                   RecordingState : int ;
const char * to_string(const RecordingState &);
namespace rose {
  namespace ecs {
    void      deserialize(RecordingState &o, IDeserializer &s);
    void        serialize(RecordingState &o, ISerializer &s);
  }
  template<>
  struct type_id<RecordingState> {
    inline static hash_value VALUE = 5552379971867693993ULL;
  };
  hash_value         hash(const RecordingState &o);
  void construct_defaults(      RecordingState &o); //implement me
}


struct                RecordingEvent;
namespace rose {
  namespace ecs {
    void        serialize(RecordingEvent &o, ISerializer &s);
    void      deserialize(RecordingEvent &o, IDeserializer &s);
  }
  hash_value         hash(const RecordingEvent &o);
  template<>
  struct type_id<RecordingEvent> {
    inline static hash_value VALUE = 1462510155760265820ULL;
  };
  void construct_defaults(      RecordingEvent &o); // implement me
}
bool operator==(const RecordingEvent &lhs, const RecordingEvent &rhs);
bool operator!=(const RecordingEvent &lhs, const RecordingEvent &rhs);

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<RecordingEvent>();
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
  
const char * to_string(const RecordingState & e) {
    switch(e) {
        case RecordingState::NONE: return "NONE";
        case RecordingState::Inactive: return "Inactive";
        case RecordingState::RecordingStart: return "RecordingStart";
        case RecordingState::Recording: return "Recording";
        case RecordingState::RecordingStop: return "RecordingStop";
        case RecordingState::ReplayingStart: return "ReplayingStart";
        case RecordingState::Replaying: return "Replaying";
        case RecordingState::ReplayingSeek: return "ReplayingSeek";
        case RecordingState::ReplayingStop: return "ReplayingStop";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(RecordingState& o, ISerializer& s) {
  switch (o) {
    case RecordingState::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case RecordingState::Inactive: {
      char str[] = "Inactive";
      serialize(str, s);
      break;
    }
    case RecordingState::RecordingStart: {
      char str[] = "RecordingStart";
      serialize(str, s);
      break;
    }
    case RecordingState::Recording: {
      char str[] = "Recording";
      serialize(str, s);
      break;
    }
    case RecordingState::RecordingStop: {
      char str[] = "RecordingStop";
      serialize(str, s);
      break;
    }
    case RecordingState::ReplayingStart: {
      char str[] = "ReplayingStart";
      serialize(str, s);
      break;
    }
    case RecordingState::Replaying: {
      char str[] = "Replaying";
      serialize(str, s);
      break;
    }
    case RecordingState::ReplayingSeek: {
      char str[] = "ReplayingSeek";
      serialize(str, s);
      break;
    }
    case RecordingState::ReplayingStop: {
      char str[] = "ReplayingStop";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(RecordingState& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = RecordingState::NONE; break;
  case rose::hash("Inactive"): o = RecordingState::Inactive; break;
  case rose::hash("RecordingStart"): o = RecordingState::RecordingStart; break;
  case rose::hash("Recording"): o = RecordingState::Recording; break;
  case rose::hash("RecordingStop"): o = RecordingState::RecordingStop; break;
  case rose::hash("ReplayingStart"): o = RecordingState::ReplayingStart; break;
  case rose::hash("Replaying"): o = RecordingState::Replaying; break;
  case rose::hash("ReplayingSeek"): o = RecordingState::ReplayingSeek; break;
  case rose::hash("ReplayingStop"): o = RecordingState::ReplayingStop; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const RecordingState& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  struct RecordingEvent
///////////////////////////////////////////////////////////////////
bool operator==(const RecordingEvent &lhs, const RecordingEvent &rhs) {
  return
    rose_parser_equals(lhs.state, rhs.state) &&
    rose_parser_equals(lhs.seek, rhs.seek) ;
}

bool operator!=(const RecordingEvent &lhs, const RecordingEvent &rhs) {
  return
    !rose_parser_equals(lhs.state, rhs.state) ||
    !rose_parser_equals(lhs.seek, rhs.seek) ;
}

void rose::ecs::serialize(RecordingEvent &o, ISerializer &s) {
  if(s.node_begin("RecordingEvent", rose::hash("RecordingEvent"), &o)) {
    s.key("state");
    serialize(o.state, s);
    s.key("seek");
    serialize(o.seek, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(RecordingEvent &o, IDeserializer &s) {
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

rose::hash_value rose::hash(const RecordingEvent &o) {
  rose::hash_value h = rose::hash(o.state);
  h = rose::xor64(h);
  h ^= rose::hash(o.seek);
  return h;
}

namespace rose::reflection {
  template <>
  const rose::reflection::TypeInfo & get_type_info<RecordingEvent>() {
    static rose::reflection::TypeInfo info = {
      /*             unique_id */ rose::hash("RecordingEvent"),
      /*           member_hash */ 1462510155760265820ULL,
      /*      memory_footprint */ sizeof(RecordingEvent),
      /*      memory_alignment */ 16,
      /*                  name */ "RecordingEvent",
      /*  fp_default_construct */ +[](void * ptr) { new (ptr) RecordingEvent(); },
      /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<RecordingEvent*>(ptr))->~RecordingEvent(); },
      /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::ecs::serialize(*std::launder(reinterpret_cast<RecordingEvent*>(ptr)), s); },
      /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::ecs::deserialize(*std::launder(reinterpret_cast<RecordingEvent*>(ptr)), d); }
    };
    return info;
  }
}


#endif
