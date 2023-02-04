#pragma once

#include <new>
#include <rose/hash.h>
#include <rose/typetraits.h>
#include <rose/serializer.h>
#include <rose/world.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN
//  command:
//    rose.parser -I .\padevents.h .\workspace.h .\path.h -O .\components_ser.h
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//  predef enum PadEventButton
///////////////////////////////////////////////////////////////////

inline rose::BoolConvertible<PadEventButton> operator|(const PadEventButton &lhs, const PadEventButton &rhs) { return { static_cast<PadEventButton>(static_cast<int >(lhs) | static_cast<int >(rhs)) }; }
inline rose::BoolConvertible<PadEventButton> operator&(const PadEventButton &lhs, const PadEventButton &rhs) { return { static_cast<PadEventButton>(static_cast<int >(lhs) & static_cast<int >(rhs)) }; }
inline rose::BoolConvertible<PadEventButton> operator^(const PadEventButton &lhs, const PadEventButton &rhs) { return { static_cast<PadEventButton>(static_cast<int >(lhs) ^ static_cast<int >(rhs)) }; }
inline PadEventButton operator|=(PadEventButton & lhs, PadEventButton rhs) { return lhs = lhs | rhs; }
inline PadEventButton operator&=(PadEventButton & lhs, PadEventButton rhs) { return lhs = lhs & rhs; }
inline PadEventButton operator^=(PadEventButton & lhs, PadEventButton rhs) { return lhs = lhs ^ rhs; }
namespace rose {
inline const char * to_string(const PadEventButton & e);
inline void serialize(PadEventButton& o, ISerializer& s);
inline void deserialize(PadEventButton& o, IDeserializer& s);
inline hash_value       hash(const PadEventButton& o);
} //namespace rose

///////////////////////////////////////////////////////////////////
//  predef enum rose::SubsystemConfig
///////////////////////////////////////////////////////////////////

inline rose::BoolConvertible<rose::SubsystemConfig> operator|(const rose::SubsystemConfig &lhs, const rose::SubsystemConfig &rhs) { return { static_cast<rose::SubsystemConfig>(static_cast<int >(lhs) | static_cast<int >(rhs)) }; }
inline rose::BoolConvertible<rose::SubsystemConfig> operator&(const rose::SubsystemConfig &lhs, const rose::SubsystemConfig &rhs) { return { static_cast<rose::SubsystemConfig>(static_cast<int >(lhs) & static_cast<int >(rhs)) }; }
inline rose::BoolConvertible<rose::SubsystemConfig> operator^(const rose::SubsystemConfig &lhs, const rose::SubsystemConfig &rhs) { return { static_cast<rose::SubsystemConfig>(static_cast<int >(lhs) ^ static_cast<int >(rhs)) }; }
inline rose::SubsystemConfig operator|=(rose::SubsystemConfig & lhs, rose::SubsystemConfig rhs) { return lhs = lhs | rhs; }
inline rose::SubsystemConfig operator&=(rose::SubsystemConfig & lhs, rose::SubsystemConfig rhs) { return lhs = lhs & rhs; }
inline rose::SubsystemConfig operator^=(rose::SubsystemConfig & lhs, rose::SubsystemConfig rhs) { return lhs = lhs ^ rhs; }
namespace rose {
inline const char * to_string(const rose::SubsystemConfig & e);
inline void serialize(rose::SubsystemConfig& o, ISerializer& s);
inline void deserialize(rose::SubsystemConfig& o, IDeserializer& s);
inline hash_value       hash(const rose::SubsystemConfig& o);
} //namespace rose

///////////////////////////////////////////////////////////////////
//  predef struct PadEvent
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const PadEvent &lhs, const PadEvent &rhs);
inline bool operator==(const PadEvent &lhs, const PadEvent &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const PadEvent &lhs, const PadEvent &rhs) { return !equals(lhs, rhs); }
inline void serialize(PadEvent &o, ISerializer &s);
inline void deserialize(PadEvent &o, IDeserializer &s);
inline hash_value hash(const PadEvent &o);

template <>
struct type_id<PadEvent>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<PadEvent>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct rose::SubsystemPath
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const rose::SubsystemPath &lhs, const rose::SubsystemPath &rhs);
inline bool operator==(const rose::SubsystemPath &lhs, const rose::SubsystemPath &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const rose::SubsystemPath &lhs, const rose::SubsystemPath &rhs) { return !equals(lhs, rhs); }
inline void serialize(rose::SubsystemPath &o, ISerializer &s);
inline void deserialize(rose::SubsystemPath &o, IDeserializer &s);
inline hash_value hash(const rose::SubsystemPath &o);

template <>
struct type_id<rose::SubsystemPath>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<rose::SubsystemPath>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct rose::Workspace
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const rose::Workspace &lhs, const rose::Workspace &rhs);
inline bool operator==(const rose::Workspace &lhs, const rose::Workspace &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const rose::Workspace &lhs, const rose::Workspace &rhs) { return !equals(lhs, rhs); }
inline void serialize(rose::Workspace &o, ISerializer &s);
inline void deserialize(rose::Workspace &o, IDeserializer &s);
inline hash_value hash(const rose::Workspace &o);

template <>
struct type_id<rose::Workspace>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<rose::Workspace>();
} //namespace rose


///////////////////////////////////////////////////////////////////
//  predef struct Path
///////////////////////////////////////////////////////////////////
namespace rose {
inline bool equals(const Path &lhs, const Path &rhs);
inline bool operator==(const Path &lhs, const Path &rhs) { return equals(lhs, rhs); }
inline bool operator!=(const Path &lhs, const Path &rhs) { return !equals(lhs, rhs); }
inline hash_value hash(const Path &o);

template <>
struct type_id<Path>;
template <>
inline const reflection::TypeInfo & reflection::get_type_info<Path>();
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
//  impl enum PadEventButton
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const PadEventButton & e) {
    switch(e) {
        case PadEventButton::NONE: return "NONE";
        case PadEventButton::PadUp: return "PadUp";
        case PadEventButton::PadDown: return "PadDown";
        case PadEventButton::PadLeft: return "PadLeft";
        case PadEventButton::PadRight: return "PadRight";
        case PadEventButton::OptionRight: return "OptionRight";
        case PadEventButton::OptionLeft: return "OptionLeft";
        case PadEventButton::LeftThumb: return "LeftThumb";
        case PadEventButton::RightThumb: return "RightThumb";
        case PadEventButton::LeftFront: return "LeftFront";
        case PadEventButton::RightFront: return "RightFront";
        case PadEventButton::South: return "South";
        case PadEventButton::East: return "East";
        case PadEventButton::West: return "West";
        case PadEventButton::North: return "North";
        case PadEventButton::LeftBack: return "LeftBack";
        case PadEventButton::RightBack: return "RightBack";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(PadEventButton& o, ISerializer& s) {
  switch (o) {
    case PadEventButton::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case PadEventButton::PadUp: {
      char str[] = "PadUp";
      serialize(str, s);
      break;
    }
    case PadEventButton::PadDown: {
      char str[] = "PadDown";
      serialize(str, s);
      break;
    }
    case PadEventButton::PadLeft: {
      char str[] = "PadLeft";
      serialize(str, s);
      break;
    }
    case PadEventButton::PadRight: {
      char str[] = "PadRight";
      serialize(str, s);
      break;
    }
    case PadEventButton::OptionRight: {
      char str[] = "OptionRight";
      serialize(str, s);
      break;
    }
    case PadEventButton::OptionLeft: {
      char str[] = "OptionLeft";
      serialize(str, s);
      break;
    }
    case PadEventButton::LeftThumb: {
      char str[] = "LeftThumb";
      serialize(str, s);
      break;
    }
    case PadEventButton::RightThumb: {
      char str[] = "RightThumb";
      serialize(str, s);
      break;
    }
    case PadEventButton::LeftFront: {
      char str[] = "LeftFront";
      serialize(str, s);
      break;
    }
    case PadEventButton::RightFront: {
      char str[] = "RightFront";
      serialize(str, s);
      break;
    }
    case PadEventButton::South: {
      char str[] = "South";
      serialize(str, s);
      break;
    }
    case PadEventButton::East: {
      char str[] = "East";
      serialize(str, s);
      break;
    }
    case PadEventButton::West: {
      char str[] = "West";
      serialize(str, s);
      break;
    }
    case PadEventButton::North: {
      char str[] = "North";
      serialize(str, s);
      break;
    }
    case PadEventButton::LeftBack: {
      char str[] = "LeftBack";
      serialize(str, s);
      break;
    }
    case PadEventButton::RightBack: {
      char str[] = "RightBack";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
inline void rose::deserialize(PadEventButton& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = PadEventButton::NONE; break;
  case rose::hash("PadUp"): o = PadEventButton::PadUp; break;
  case rose::hash("PadDown"): o = PadEventButton::PadDown; break;
  case rose::hash("PadLeft"): o = PadEventButton::PadLeft; break;
  case rose::hash("PadRight"): o = PadEventButton::PadRight; break;
  case rose::hash("OptionRight"): o = PadEventButton::OptionRight; break;
  case rose::hash("OptionLeft"): o = PadEventButton::OptionLeft; break;
  case rose::hash("LeftThumb"): o = PadEventButton::LeftThumb; break;
  case rose::hash("RightThumb"): o = PadEventButton::RightThumb; break;
  case rose::hash("LeftFront"): o = PadEventButton::LeftFront; break;
  case rose::hash("RightFront"): o = PadEventButton::RightFront; break;
  case rose::hash("South"): o = PadEventButton::South; break;
  case rose::hash("East"): o = PadEventButton::East; break;
  case rose::hash("West"): o = PadEventButton::West; break;
  case rose::hash("North"): o = PadEventButton::North; break;
  case rose::hash("LeftBack"): o = PadEventButton::LeftBack; break;
  case rose::hash("RightBack"): o = PadEventButton::RightBack; break;
  default: /*unknown value*/ break;
  }
}
inline rose::hash_value rose::hash(const PadEventButton& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  impl enum rose::SubsystemConfig
///////////////////////////////////////////////////////////////////
inline const char * rose::to_string(const rose::SubsystemConfig & e) {
    switch(e) {
        case rose::SubsystemConfig::NONE: return "NONE";
        case rose::SubsystemConfig::Active: return "Active";
        default: return "<UNKNOWN>";
    }
}
inline void rose::serialize(rose::SubsystemConfig& o, ISerializer& s) {
  switch (o) {
    case rose::SubsystemConfig::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case rose::SubsystemConfig::Active: {
      char str[] = "Active";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
inline void rose::deserialize(rose::SubsystemConfig& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = rose::SubsystemConfig::NONE; break;
  case rose::hash("Active"): o = rose::SubsystemConfig::Active; break;
  default: /*unknown value*/ break;
  }
}
inline rose::hash_value rose::hash(const rose::SubsystemConfig& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  impl struct PadEvent
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const PadEvent &lhs, const PadEvent &rhs) {
  return
    rose::rose_parser_equals(lhs.stick_lx, rhs.stick_lx) &&
    rose::rose_parser_equals(lhs.stick_ly, rhs.stick_ly) &&
    rose::rose_parser_equals(lhs.stick_rx, rhs.stick_rx) &&
    rose::rose_parser_equals(lhs.stick_ry, rhs.stick_ry) &&
    rose::rose_parser_equals(lhs.trigger_l, rhs.trigger_l) &&
    rose::rose_parser_equals(lhs.trigger_r, rhs.trigger_r) &&
    rose::rose_parser_equals(lhs.buttons, rhs.buttons) &&
    rose::rose_parser_equals(lhs.player, rhs.player);
}

inline void rose::serialize(PadEvent &o, ISerializer &s) {
  if(s.node_begin("PadEvent", hash("PadEvent"), &o)) {
    s.key("stick_lx");
    serialize(o.stick_lx, s);
    s.key("stick_ly");
    serialize(o.stick_ly, s);
    s.key("stick_rx");
    serialize(o.stick_rx, s);
    s.key("stick_ry");
    serialize(o.stick_ry, s);
    s.key("trigger_l");
    serialize(o.trigger_l, s);
    s.key("trigger_r");
    serialize(o.trigger_r, s);
    s.key("buttons");
    serialize(o.buttons, s);
    s.key("player");
    serialize(o.player, s);
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(PadEvent &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("stick_lx"):
        deserialize(o.stick_lx, s);
        break;
      case rose::hash("stick_ly"):
        deserialize(o.stick_ly, s);
        break;
      case rose::hash("stick_rx"):
        deserialize(o.stick_rx, s);
        break;
      case rose::hash("stick_ry"):
        deserialize(o.stick_ry, s);
        break;
      case rose::hash("trigger_l"):
        deserialize(o.trigger_l, s);
        break;
      case rose::hash("trigger_r"):
        deserialize(o.trigger_r, s);
        break;
      case rose::hash("buttons"):
        deserialize(o.buttons, s);
        break;
      case rose::hash("player"):
        deserialize(o.player, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline rose::hash_value rose::hash(const PadEvent &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.stick_lx);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.stick_ly);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.stick_rx);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.stick_ry);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.trigger_l);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.trigger_r);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.buttons);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.player);
  return h;
}

template <>
struct rose::type_id<PadEvent> {
    inline static rose::hash_value VALUE = 2480295155421047372ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<PadEvent>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("PadEvent"),
    /*           member_hash */ 2480295155421047372ULL,
    /*      memory_footprint */ sizeof(PadEvent),
    /*      memory_alignment */ 16,
    /*                  name */ "PadEvent",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) PadEvent(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<PadEvent*>(ptr))->~PadEvent(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<PadEvent*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<PadEvent*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct rose::SubsystemPath
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const rose::SubsystemPath &lhs, const rose::SubsystemPath &rhs) {
  return
    rose::rose_parser_equals(lhs.path, rhs.path) &&
    rose::rose_parser_equals(lhs.config, rhs.config);
}

inline void rose::serialize(rose::SubsystemPath &o, ISerializer &s) {
  if(s.node_begin("rose::SubsystemPath", hash("rose::SubsystemPath"), &o)) {
    s.key("path");
    serialize(o.path, s);
    s.key("config");
    serialize(o.config, s);
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(rose::SubsystemPath &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("path"):
        deserialize(o.path, s);
        break;
      case rose::hash("config"):
        deserialize(o.config, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline rose::hash_value rose::hash(const rose::SubsystemPath &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.path);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.config);
  return h;
}

template <>
struct rose::type_id<rose::SubsystemPath> {
    inline static rose::hash_value VALUE = 5383390033191037884ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<rose::SubsystemPath>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("rose::SubsystemPath"),
    /*           member_hash */ 5383390033191037884ULL,
    /*      memory_footprint */ sizeof(rose::SubsystemPath),
    /*      memory_alignment */ 16,
    /*                  name */ "rose::SubsystemPath",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) rose::SubsystemPath(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<rose::SubsystemPath*>(ptr))->~SubsystemPath(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<rose::SubsystemPath*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<rose::SubsystemPath*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct rose::Workspace
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const rose::Workspace &lhs, const rose::Workspace &rhs) {
  return
    rose::rose_parser_equals(lhs.subsystems, rhs.subsystems) &&
    rose::rose_parser_equals(lhs.console_filter, rhs.console_filter);
}

inline void rose::serialize(rose::Workspace &o, ISerializer &s) {
  if(s.node_begin("rose::Workspace", hash("rose::Workspace"), &o)) {
    s.key("subsystems");
    serialize(o.subsystems, s);
    s.key("console_filter");
    serialize(o.console_filter, s, std::strlen(o.console_filter));
    s.node_end();
  }
  s.end();
}

inline void rose::deserialize(rose::Workspace &o, IDeserializer &s) {
  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("subsystems"):
        deserialize(o.subsystems, s);
        break;
      case rose::hash("console_filter"):
        deserialize(o.console_filter, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

inline rose::hash_value rose::hash(const rose::Workspace &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.subsystems);
  h = rose::xor64(h);
  h ^= rose::rose_parser_hash(o.console_filter);
  return h;
}

template <>
struct rose::type_id<rose::Workspace> {
    inline static rose::hash_value VALUE = 9747542806317341572ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<rose::Workspace>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("rose::Workspace"),
    /*           member_hash */ 9747542806317341572ULL,
    /*      memory_footprint */ sizeof(rose::Workspace),
    /*      memory_alignment */ 16,
    /*                  name */ "rose::Workspace",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) rose::Workspace(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<rose::Workspace*>(ptr))->~Workspace(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<rose::Workspace*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<rose::Workspace*>(ptr)), d); }
  };
  return info;
}

///////////////////////////////////////////////////////////////////
//  impl struct Path
///////////////////////////////////////////////////////////////////
inline bool rose::equals(const Path &lhs, const Path &rhs) {
  return
    rose::rose_parser_equals(lhs.string, rhs.string);
}

inline rose::hash_value rose::hash(const Path &o) {
  rose::hash_value h = 0;
  h ^= rose::rose_parser_hash(o.string);
  return h;
}

template <>
struct rose::type_id<Path> {
    inline static rose::hash_value VALUE = 18284124119257047942ULL;
};

template <>
inline const rose::reflection::TypeInfo & rose::reflection::get_type_info<Path>() {
  static rose::reflection::TypeInfo info = {
    /*             unique_id */ rose::hash("Path"),
    /*           member_hash */ 18284124119257047942ULL,
    /*      memory_footprint */ sizeof(Path),
    /*      memory_alignment */ 16,
    /*                  name */ "Path",
    /*  fp_default_construct */ +[](void * ptr) { new (ptr) Path(); },
    /*   fp_default_destruct */ +[](void * ptr) { std::launder(reinterpret_cast<Path*>(ptr))->~Path(); },
    /*          fp_serialize */ +[](void * ptr, ISerializer & s) { ::rose::serialize(*std::launder(reinterpret_cast<Path*>(ptr)), s); },
    /*        fp_deserialize */ +[](void * ptr, IDeserializer & d) { ::rose::deserialize(*std::launder(reinterpret_cast<Path*>(ptr)), d); }
  };
  return info;
}

