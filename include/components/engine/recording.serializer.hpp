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

namespace rose {
enum class                   RoseRecordingState : int ;
}
const char * to_string(const rose::RoseRecordingState &);
namespace rose {
  void      deserialize(rose::RoseRecordingState &o, IDeserializer &s);
  void        serialize(rose::RoseRecordingState &o, ISerializer &s);
  template<>
  struct type_id<rose::RoseRecordingState> {
    inline static hash_value VALUE = 9428585348312703707ULL;
  };
  hash_value         hash(const rose::RoseRecordingState &o);
  void construct_defaults(      rose::RoseRecordingState &o); //implement me
}

inline BoolConvertible<rose::RoseRecordingState, int > operator|(const rose::RoseRecordingState &a, const rose::RoseRecordingState &b) { return { static_cast<rose::RoseRecordingState>(static_cast<int >(a) | static_cast<int >(b)) }; }
inline BoolConvertible<rose::RoseRecordingState, int > operator&(const rose::RoseRecordingState &a, const rose::RoseRecordingState &b) { return { static_cast<rose::RoseRecordingState>(static_cast<int >(a) & static_cast<int >(b)) }; }
inline BoolConvertible<rose::RoseRecordingState, int > operator^(const rose::RoseRecordingState &a, const rose::RoseRecordingState &b) { return { static_cast<rose::RoseRecordingState>(static_cast<int >(a) ^ static_cast<int >(b)) }; }
inline rose::RoseRecordingState operator|=(rose::RoseRecordingState &a, rose::RoseRecordingState b) { return a = a | b; }
inline rose::RoseRecordingState operator&=(rose::RoseRecordingState &a, rose::RoseRecordingState b) { return a = a & b; }
inline rose::RoseRecordingState operator^=(rose::RoseRecordingState &a, rose::RoseRecordingState b) { return a = a ^ b; }


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
  
const char * to_string(const rose::RoseRecordingState & e) {
    switch(e) {
        case rose::RoseRecordingState::NONE: return "NONE";
        case rose::RoseRecordingState::Inactive: return "Inactive";
        case rose::RoseRecordingState::Paused: return "Paused";
        case rose::RoseRecordingState::Delete: return "Delete";
        case rose::RoseRecordingState::RecordingMask: return "RecordingMask";
        case rose::RoseRecordingState::RecordingStart: return "RecordingStart";
        case rose::RoseRecordingState::Recording: return "Recording";
        case rose::RoseRecordingState::RecordingStop: return "RecordingStop";
        case rose::RoseRecordingState::ReplayingMask: return "ReplayingMask";
        case rose::RoseRecordingState::ReplayingStart: return "ReplayingStart";
        case rose::RoseRecordingState::Replaying: return "Replaying";
        case rose::RoseRecordingState::ReplayingSeek: return "ReplayingSeek";
        case rose::RoseRecordingState::ReplayingStop: return "ReplayingStop";
        default: return "<UNKNOWN>";
    }
}
void rose::serialize(rose::RoseRecordingState& o, ISerializer& s) {
  switch (o) {
    case rose::RoseRecordingState::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::Inactive: {
      char str[] = "Inactive";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::Paused: {
      char str[] = "Paused";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::Delete: {
      char str[] = "Delete";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::RecordingMask: {
      char str[] = "RecordingMask";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::RecordingStart: {
      char str[] = "RecordingStart";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::Recording: {
      char str[] = "Recording";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::RecordingStop: {
      char str[] = "RecordingStop";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::ReplayingMask: {
      char str[] = "ReplayingMask";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::ReplayingStart: {
      char str[] = "ReplayingStart";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::Replaying: {
      char str[] = "Replaying";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::ReplayingSeek: {
      char str[] = "ReplayingSeek";
      serialize(str, s);
      break;
    }
    case rose::RoseRecordingState::ReplayingStop: {
      char str[] = "ReplayingStop";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::deserialize(rose::RoseRecordingState& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = rose::RoseRecordingState::NONE; break;
  case rose::hash("Inactive"): o = rose::RoseRecordingState::Inactive; break;
  case rose::hash("Paused"): o = rose::RoseRecordingState::Paused; break;
  case rose::hash("Delete"): o = rose::RoseRecordingState::Delete; break;
  case rose::hash("RecordingMask"): o = rose::RoseRecordingState::RecordingMask; break;
  case rose::hash("RecordingStart"): o = rose::RoseRecordingState::RecordingStart; break;
  case rose::hash("Recording"): o = rose::RoseRecordingState::Recording; break;
  case rose::hash("RecordingStop"): o = rose::RoseRecordingState::RecordingStop; break;
  case rose::hash("ReplayingMask"): o = rose::RoseRecordingState::ReplayingMask; break;
  case rose::hash("ReplayingStart"): o = rose::RoseRecordingState::ReplayingStart; break;
  case rose::hash("Replaying"): o = rose::RoseRecordingState::Replaying; break;
  case rose::hash("ReplayingSeek"): o = rose::RoseRecordingState::ReplayingSeek; break;
  case rose::hash("ReplayingStop"): o = rose::RoseRecordingState::ReplayingStop; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const rose::RoseRecordingState& o) {
  return static_cast<rose::hash_value>(o);
}


#endif
