#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN
//  command:
//    rose.parser -I .\engine\recording.h -O .\engine\recording.serializer.hpp
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  predef enum rose::RRecordingState
///////////////////////////////////////////////////////////////////

inline rose::BoolConvertible<rose::RRecordingState> operator|(const rose::RRecordingState &lhs, const rose::RRecordingState &rhs) { return { static_cast<rose::RRecordingState>(static_cast<int >(lhs) | static_cast<int >(rhs)) }; }
inline rose::BoolConvertible<rose::RRecordingState> operator&(const rose::RRecordingState &lhs, const rose::RRecordingState &rhs) { return { static_cast<rose::RRecordingState>(static_cast<int >(lhs) & static_cast<int >(rhs)) }; }
inline rose::BoolConvertible<rose::RRecordingState> operator^(const rose::RRecordingState &lhs, const rose::RRecordingState &rhs) { return { static_cast<rose::RRecordingState>(static_cast<int >(lhs) ^ static_cast<int >(rhs)) }; }
inline rose::RRecordingState operator|=(rose::RRecordingState & lhs, rose::RRecordingState rhs) { return lhs = lhs | rhs; }
inline rose::RRecordingState operator&=(rose::RRecordingState & lhs, rose::RRecordingState rhs) { return lhs = lhs & rhs; }
inline rose::RRecordingState operator^=(rose::RRecordingState & lhs, rose::RRecordingState rhs) { return lhs = lhs ^ rhs; }
namespace rose {
inline const char * to_string(const rose::RRecordingState & e);
inline void serialize(rose::RRecordingState& o, ISerializer& s);
inline void deserialize(rose::RRecordingState& o, IDeserializer& s);
inline RHash       hash(const rose::RRecordingState& o);
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
RHash rose_parser_hash(const T & value) { return hash(value); }

template<class T>
RHash rose_parser_hash(const std::vector<T>& v) {
  RHash h = 0;
  for (const auto& o : v) {
    h ^= rose_parser_hash(o);
    h = xor64(h);
  }
  return h;
}

}
#endif
  
///////////////////////////////////////////////////////////////////
//  impl enum rose::RRecordingState
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const rose::RRecordingState & e) {
    switch(e) {
        case rose::RRecordingState::NONE: return "NONE";
        case rose::RRecordingState::Inactive: return "Inactive";
        case rose::RRecordingState::Paused: return "Paused";
        case rose::RRecordingState::Delete: return "Delete";
        case rose::RRecordingState::RecordingMask: return "RecordingMask";
        case rose::RRecordingState::RecordingStart: return "RecordingStart";
        case rose::RRecordingState::Recording: return "Recording";
        case rose::RRecordingState::RecordingStop: return "RecordingStop";
        case rose::RRecordingState::ReplayingMask: return "ReplayingMask";
        case rose::RRecordingState::ReplayingStart: return "ReplayingStart";
        case rose::RRecordingState::Replaying: return "Replaying";
        case rose::RRecordingState::ReplayingSeek: return "ReplayingSeek";
        case rose::RRecordingState::ReplayingStop: return "ReplayingStop";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(rose::RRecordingState& o, ISerializer& s) {
  switch (o) {
    case rose::RRecordingState::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::Inactive: {
      char str[] = "Inactive";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::Paused: {
      char str[] = "Paused";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::Delete: {
      char str[] = "Delete";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::RecordingMask: {
      char str[] = "RecordingMask";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::RecordingStart: {
      char str[] = "RecordingStart";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::Recording: {
      char str[] = "Recording";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::RecordingStop: {
      char str[] = "RecordingStop";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::ReplayingMask: {
      char str[] = "ReplayingMask";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::ReplayingStart: {
      char str[] = "ReplayingStart";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::Replaying: {
      char str[] = "Replaying";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::ReplayingSeek: {
      char str[] = "ReplayingSeek";
      serialize(str, s);
      break;
    }
    case rose::RRecordingState::ReplayingStop: {
      char str[] = "ReplayingStop";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
inline void rose::deserialize(rose::RRecordingState& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  RHash h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = rose::RRecordingState::NONE; break;
  case rose::hash("Inactive"): o = rose::RRecordingState::Inactive; break;
  case rose::hash("Paused"): o = rose::RRecordingState::Paused; break;
  case rose::hash("Delete"): o = rose::RRecordingState::Delete; break;
  case rose::hash("RecordingMask"): o = rose::RRecordingState::RecordingMask; break;
  case rose::hash("RecordingStart"): o = rose::RRecordingState::RecordingStart; break;
  case rose::hash("Recording"): o = rose::RRecordingState::Recording; break;
  case rose::hash("RecordingStop"): o = rose::RRecordingState::RecordingStop; break;
  case rose::hash("ReplayingMask"): o = rose::RRecordingState::ReplayingMask; break;
  case rose::hash("ReplayingStart"): o = rose::RRecordingState::ReplayingStart; break;
  case rose::hash("Replaying"): o = rose::RRecordingState::Replaying; break;
  case rose::hash("ReplayingSeek"): o = rose::RRecordingState::ReplayingSeek; break;
  case rose::hash("ReplayingStop"): o = rose::RRecordingState::ReplayingStop; break;
  default: /*unknown value*/ break;
  }
}
inline RHash rose::hash(const rose::RRecordingState& o) {
  return static_cast<RHash>(o);
}

