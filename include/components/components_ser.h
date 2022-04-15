#pragma once

#include <rose/hash.h>
#include <rose/typetraits.h>
#include <serializer/serializer.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser -I .\padevents.h .\workspace.h .\path.h -O .\components_ser.h
///////////////////////////////////////////////////////////////////

enum class                   PadEventButton : int ;
const char * to_string(const PadEventButton &);
namespace rose {
  namespace ecs {
    void      deserialize(PadEventButton &o, IDeserializer &s);
    void        serialize(PadEventButton &o, ISerializer &s);
  }
  template<>
  struct type_id<PadEventButton> {
    inline static hash_value VALUE = 13001520524004003403ULL;
  };
  hash_value         hash(const PadEventButton &o);
  void construct_defaults(      PadEventButton &o); //implement me
}

inline PadEventButton operator|(const PadEventButton &a, const PadEventButton &b) { return static_cast<PadEventButton>(static_cast<int >(a) | static_cast<int >(b)); }
inline PadEventButton operator|=(PadEventButton &a, const PadEventButton &b) { return a = a | b; }
inline PadEventButton operator&(const PadEventButton &a, const PadEventButton &b) { return static_cast<PadEventButton>(static_cast<int >(a) & static_cast<int >(b)); }
inline PadEventButton operator&=(PadEventButton &a, const PadEventButton &b) { return a = a & b; }
inline PadEventButton operator^(const PadEventButton &a, const PadEventButton &b) { return static_cast<PadEventButton>(static_cast<int >(a) ^ static_cast<int >(b)); }
inline PadEventButton operator^=(PadEventButton &a, const PadEventButton &b) { return a = a ^ b; }
inline bool operator!(const PadEventButton &e) { return static_cast<int >(e) == 0; }


enum class                   rose::ecs::SubsystemConfig : int ;
const char * to_string(const rose::ecs::SubsystemConfig &);
namespace rose {
  namespace ecs {
    void      deserialize(rose::ecs::SubsystemConfig &o, IDeserializer &s);
    void        serialize(rose::ecs::SubsystemConfig &o, ISerializer &s);
  }
  template<>
  struct type_id<rose::ecs::SubsystemConfig> {
    inline static hash_value VALUE = 11689830927128042884ULL;
  };
  hash_value         hash(const rose::ecs::SubsystemConfig &o);
  void construct_defaults(      rose::ecs::SubsystemConfig &o); //implement me
}

inline rose::ecs::SubsystemConfig operator|(const rose::ecs::SubsystemConfig &a, const rose::ecs::SubsystemConfig &b) { return static_cast<rose::ecs::SubsystemConfig>(static_cast<int >(a) | static_cast<int >(b)); }
inline rose::ecs::SubsystemConfig operator|=(rose::ecs::SubsystemConfig &a, const rose::ecs::SubsystemConfig &b) { return a = a | b; }
inline rose::ecs::SubsystemConfig operator&(const rose::ecs::SubsystemConfig &a, const rose::ecs::SubsystemConfig &b) { return static_cast<rose::ecs::SubsystemConfig>(static_cast<int >(a) & static_cast<int >(b)); }
inline rose::ecs::SubsystemConfig operator&=(rose::ecs::SubsystemConfig &a, const rose::ecs::SubsystemConfig &b) { return a = a & b; }
inline rose::ecs::SubsystemConfig operator^(const rose::ecs::SubsystemConfig &a, const rose::ecs::SubsystemConfig &b) { return static_cast<rose::ecs::SubsystemConfig>(static_cast<int >(a) ^ static_cast<int >(b)); }
inline rose::ecs::SubsystemConfig operator^=(rose::ecs::SubsystemConfig &a, const rose::ecs::SubsystemConfig &b) { return a = a ^ b; }
inline bool operator!(const rose::ecs::SubsystemConfig &e) { return static_cast<int >(e) == 0; }


struct                PadEvent;
namespace rose {
  namespace ecs {
    void        serialize(PadEvent &o, ISerializer &s);
    void      deserialize(PadEvent &o, IDeserializer &s);
  }
  hash_value         hash(const PadEvent &o);
  template<>
  struct type_id<PadEvent> {
    inline static hash_value VALUE = 918484592891382733ULL;
  };
  void construct_defaults(      PadEvent &o); // implement me
}
bool operator==(const PadEvent &lhs, const PadEvent &rhs);
bool operator!=(const PadEvent &lhs, const PadEvent &rhs);


struct                rose::ecs::SubsystemPath;
namespace rose {
  namespace ecs {
    void        serialize(rose::ecs::SubsystemPath &o, ISerializer &s);
    void      deserialize(rose::ecs::SubsystemPath &o, IDeserializer &s);
  }
  hash_value         hash(const rose::ecs::SubsystemPath &o);
  template<>
  struct type_id<rose::ecs::SubsystemPath> {
    inline static hash_value VALUE = 13148833942642572779ULL;
  };
  void construct_defaults(      rose::ecs::SubsystemPath &o); // implement me
}
bool operator==(const rose::ecs::SubsystemPath &lhs, const rose::ecs::SubsystemPath &rhs);
bool operator!=(const rose::ecs::SubsystemPath &lhs, const rose::ecs::SubsystemPath &rhs);


struct                rose::ecs::Workspace;
namespace rose {
  namespace ecs {
    void        serialize(rose::ecs::Workspace &o, ISerializer &s);
    void      deserialize(rose::ecs::Workspace &o, IDeserializer &s);
  }
  hash_value         hash(const rose::ecs::Workspace &o);
  template<>
  struct type_id<rose::ecs::Workspace> {
    inline static hash_value VALUE = 3466511763420867999ULL;
  };
  void construct_defaults(      rose::ecs::Workspace &o); // implement me
}
bool operator==(const rose::ecs::Workspace &lhs, const rose::ecs::Workspace &rhs);
bool operator!=(const rose::ecs::Workspace &lhs, const rose::ecs::Workspace &rhs);


struct                path;
namespace rose {
  namespace ecs {
  }
  hash_value         hash(const path &o);
  template<>
  struct type_id<path> {
    inline static hash_value VALUE = 8944715875326514183ULL;
  };
  void construct_defaults(      path &o); // implement me
}
bool operator==(const path &lhs, const path &rhs);
bool operator!=(const path &lhs, const path &rhs);


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
  
const char * to_string(const PadEventButton & e) {
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
void rose::ecs::serialize(PadEventButton& o, ISerializer& s) {
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
void rose::ecs::deserialize(PadEventButton& o, IDeserializer& s) {
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
rose::hash_value       rose::hash(const PadEventButton& o) {
  return static_cast<rose::hash_value>(o);
}

const char * to_string(const rose::ecs::SubsystemConfig & e) {
    switch(e) {
        case rose::ecs::SubsystemConfig::NONE: return "NONE";
        case rose::ecs::SubsystemConfig::Active: return "Active";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(rose::ecs::SubsystemConfig& o, ISerializer& s) {
  switch (o) {
    case rose::ecs::SubsystemConfig::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case rose::ecs::SubsystemConfig::Active: {
      char str[] = "Active";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(rose::ecs::SubsystemConfig& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = rose::ecs::SubsystemConfig::NONE; break;
  case rose::hash("Active"): o = rose::ecs::SubsystemConfig::Active; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const rose::ecs::SubsystemConfig& o) {
  return static_cast<rose::hash_value>(o);
}

///////////////////////////////////////////////////////////////////
//  struct PadEvent
///////////////////////////////////////////////////////////////////
bool operator==(const PadEvent &lhs, const PadEvent &rhs) {
  return
    rose_parser_equals(lhs.stick_lx, rhs.stick_lx) &&
    rose_parser_equals(lhs.stick_ly, rhs.stick_ly) &&
    rose_parser_equals(lhs.stick_rx, rhs.stick_rx) &&
    rose_parser_equals(lhs.stick_ry, rhs.stick_ry) &&
    rose_parser_equals(lhs.trigger_l, rhs.trigger_l) &&
    rose_parser_equals(lhs.trigger_r, rhs.trigger_r) &&
    rose_parser_equals(lhs.buttons, rhs.buttons) &&
    rose_parser_equals(lhs.player, rhs.player) ;
}

bool operator!=(const PadEvent &lhs, const PadEvent &rhs) {
  return
    !rose_parser_equals(lhs.stick_lx, rhs.stick_lx) ||
    !rose_parser_equals(lhs.stick_ly, rhs.stick_ly) ||
    !rose_parser_equals(lhs.stick_rx, rhs.stick_rx) ||
    !rose_parser_equals(lhs.stick_ry, rhs.stick_ry) ||
    !rose_parser_equals(lhs.trigger_l, rhs.trigger_l) ||
    !rose_parser_equals(lhs.trigger_r, rhs.trigger_r) ||
    !rose_parser_equals(lhs.buttons, rhs.buttons) ||
    !rose_parser_equals(lhs.player, rhs.player) ;
}

void rose::ecs::serialize(PadEvent &o, ISerializer &s) {
  if(s.node_begin("PadEvent", rose::hash("PadEvent"), &o)) {
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

void rose::ecs::deserialize(PadEvent &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

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

rose::hash_value rose::hash(const PadEvent &o) {
  rose::hash_value h = rose::hash(o.stick_lx);
  h = rose::xor64(h);
  h ^= rose::hash(o.stick_ly);
  h = rose::xor64(h);
  h ^= rose::hash(o.stick_rx);
  h = rose::xor64(h);
  h ^= rose::hash(o.stick_ry);
  h = rose::xor64(h);
  h ^= rose::hash(o.trigger_l);
  h = rose::xor64(h);
  h ^= rose::hash(o.trigger_r);
  h = rose::xor64(h);
  h ^= rose::hash(o.buttons);
  h = rose::xor64(h);
  h ^= rose::hash(o.player);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct rose::ecs::SubsystemPath
///////////////////////////////////////////////////////////////////
bool operator==(const rose::ecs::SubsystemPath &lhs, const rose::ecs::SubsystemPath &rhs) {
  return
    rose_parser_equals(lhs.path, rhs.path) &&
    rose_parser_equals(lhs.config, rhs.config) ;
}

bool operator!=(const rose::ecs::SubsystemPath &lhs, const rose::ecs::SubsystemPath &rhs) {
  return
    !rose_parser_equals(lhs.path, rhs.path) ||
    !rose_parser_equals(lhs.config, rhs.config) ;
}

void rose::ecs::serialize(rose::ecs::SubsystemPath &o, ISerializer &s) {
  if(s.node_begin("rose::ecs::SubsystemPath", rose::hash("rose::ecs::SubsystemPath"), &o)) {
    s.key("path");
    serialize(o.path, s);
    s.key("config");
    serialize(o.config, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(rose::ecs::SubsystemPath &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

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

rose::hash_value rose::hash(const rose::ecs::SubsystemPath &o) {
  rose::hash_value h = rose::hash(o.path);
  h = rose::xor64(h);
  h ^= rose::hash(o.config);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct rose::ecs::Workspace
///////////////////////////////////////////////////////////////////
bool operator==(const rose::ecs::Workspace &lhs, const rose::ecs::Workspace &rhs) {
  return
    rose_parser_equals(lhs.subsystems, rhs.subsystems) &&
    rose_parser_equals(lhs.console_filter, rhs.console_filter) ;
}

bool operator!=(const rose::ecs::Workspace &lhs, const rose::ecs::Workspace &rhs) {
  return
    !rose_parser_equals(lhs.subsystems, rhs.subsystems) ||
    !rose_parser_equals(lhs.console_filter, rhs.console_filter) ;
}

void rose::ecs::serialize(rose::ecs::Workspace &o, ISerializer &s) {
  if(s.node_begin("rose::ecs::Workspace", rose::hash("rose::ecs::Workspace"), &o)) {
    s.key("subsystems");
    serialize(o.subsystems, s);
    s.key("console_filter");
    serialize(o.console_filter, s, std::strlen(o.console_filter));
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(rose::ecs::Workspace &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

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

rose::hash_value rose::hash(const rose::ecs::Workspace &o) {
  rose::hash_value h = rose::hash(o.subsystems);
  h = rose::xor64(h);
  h ^= rose::hash(o.console_filter);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct path
///////////////////////////////////////////////////////////////////
bool operator==(const path &lhs, const path &rhs) {
  return
    rose_parser_equals(lhs.string, rhs.string) ;
}

bool operator!=(const path &lhs, const path &rhs) {
  return
    !rose_parser_equals(lhs.string, rhs.string) ;
}

rose::hash_value rose::hash(const path &o) {
  rose::hash_value h = rose::hash(o.string);
  return h;
}

#endif
