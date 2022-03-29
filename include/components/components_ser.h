#pragma once

#include <rose/hash.h>
#include <rose/typetraits.h>
#include <serializer/serializer.h>

///////////////////////////////////////////////////////////////////
//  AUTOGEN                                                      //
//  command:
//    rose.parser -I .\padevents.h .\workspace.h -O .\components_ser.h
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
inline bool operator!(const PadEventButton &e) { return static_cast<int >(e) == 0; }


enum class                   SubsystemConfig : int ;
const char * to_string(const SubsystemConfig &);
namespace rose {
  namespace ecs {
    void      deserialize(SubsystemConfig &o, IDeserializer &s);
    void        serialize(SubsystemConfig &o, ISerializer &s);
  }
  template<>
  struct type_id<SubsystemConfig> {
    inline static hash_value VALUE = 6192715053991086075ULL;
  };
  hash_value         hash(const SubsystemConfig &o);
  void construct_defaults(      SubsystemConfig &o); //implement me
}

inline SubsystemConfig operator|(const SubsystemConfig &a, const SubsystemConfig &b) { return static_cast<SubsystemConfig>(static_cast<int >(a) | static_cast<int >(b)); }
inline SubsystemConfig operator|=(SubsystemConfig &a, const SubsystemConfig &b) { return a = a | b; }
inline SubsystemConfig operator&(const SubsystemConfig &a, const SubsystemConfig &b) { return static_cast<SubsystemConfig>(static_cast<int >(a) & static_cast<int >(b)); }
inline SubsystemConfig operator&=(SubsystemConfig &a, const SubsystemConfig &b) { return a = a & b; }
inline bool operator!(const SubsystemConfig &e) { return static_cast<int >(e) == 0; }


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


struct                SubsystemPath;
namespace rose {
  namespace ecs {
    void        serialize(SubsystemPath &o, ISerializer &s);
    void      deserialize(SubsystemPath &o, IDeserializer &s);
  }
  hash_value         hash(const SubsystemPath &o);
  template<>
  struct type_id<SubsystemPath> {
    inline static hash_value VALUE = 15506991714936396707ULL;
  };
  void construct_defaults(      SubsystemPath &o); // implement me
}
bool operator==(const SubsystemPath &lhs, const SubsystemPath &rhs);
bool operator!=(const SubsystemPath &lhs, const SubsystemPath &rhs);


struct                WorkspacePath;
namespace rose {
  namespace ecs {
    void        serialize(WorkspacePath &o, ISerializer &s);
    void      deserialize(WorkspacePath &o, IDeserializer &s);
  }
  hash_value         hash(const WorkspacePath &o);
  template<>
  struct type_id<WorkspacePath> {
    inline static hash_value VALUE = 17356310555021850461ULL;
  };
  void construct_defaults(      WorkspacePath &o); // implement me
}
bool operator==(const WorkspacePath &lhs, const WorkspacePath &rhs);
bool operator!=(const WorkspacePath &lhs, const WorkspacePath &rhs);


struct                Workspace;
namespace rose {
  namespace ecs {
    void        serialize(Workspace &o, ISerializer &s);
    void      deserialize(Workspace &o, IDeserializer &s);
  }
  hash_value         hash(const Workspace &o);
  template<>
  struct type_id<Workspace> {
    inline static hash_value VALUE = 16052463485792588602ULL;
  };
  void construct_defaults(      Workspace &o); // implement me
}
bool operator==(const Workspace &lhs, const Workspace &rhs);
bool operator!=(const Workspace &lhs, const Workspace &rhs);


struct                WorkspaceConfig;
namespace rose {
  namespace ecs {
    void        serialize(WorkspaceConfig &o, ISerializer &s);
    void      deserialize(WorkspaceConfig &o, IDeserializer &s);
  }
  hash_value         hash(const WorkspaceConfig &o);
  template<>
  struct type_id<WorkspaceConfig> {
    inline static hash_value VALUE = 2384895658567893362ULL;
  };
  void construct_defaults(      WorkspaceConfig &o); // implement me
}
bool operator==(const WorkspaceConfig &lhs, const WorkspaceConfig &rhs);
bool operator!=(const WorkspaceConfig &lhs, const WorkspaceConfig &rhs);


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

const char * to_string(const SubsystemConfig & e) {
    switch(e) {
        case SubsystemConfig::NONE: return "NONE";
        case SubsystemConfig::Active: return "Active";
        default: return "<UNKNOWN>";
    }
}
void rose::ecs::serialize(SubsystemConfig& o, ISerializer& s) {
  switch (o) {
    case SubsystemConfig::NONE: {
      char str[] = "NONE";
      serialize(str, s);
      break;
    }
    case SubsystemConfig::Active: {
      char str[] = "Active";
      serialize(str, s);
      break;
    }
    default: /* unknown */ break;
  }
}
void rose::ecs::deserialize(SubsystemConfig& o, IDeserializer& s) {
  char str[64];
  deserialize(str, s);
  rose::hash_value h = rose::hash(str);
  switch (h) {
  case rose::hash("NONE"): o = SubsystemConfig::NONE; break;
  case rose::hash("Active"): o = SubsystemConfig::Active; break;
  default: /*unknown value*/ break;
  }
}
rose::hash_value       rose::hash(const SubsystemConfig& o) {
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
//  struct SubsystemPath
///////////////////////////////////////////////////////////////////
bool operator==(const SubsystemPath &lhs, const SubsystemPath &rhs) {
  return
    rose_parser_equals(lhs.path, rhs.path) &&
    rose_parser_equals(lhs.config, rhs.config) ;
}

bool operator!=(const SubsystemPath &lhs, const SubsystemPath &rhs) {
  return
    !rose_parser_equals(lhs.path, rhs.path) ||
    !rose_parser_equals(lhs.config, rhs.config) ;
}

void rose::ecs::serialize(SubsystemPath &o, ISerializer &s) {
  if(s.node_begin("SubsystemPath", rose::hash("SubsystemPath"), &o)) {
    s.key("path");
    serialize(o.path, s, std::strlen(o.path));
    s.key("config");
    serialize(o.config, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(SubsystemPath &o, IDeserializer &s) {
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

rose::hash_value rose::hash(const SubsystemPath &o) {
  rose::hash_value h = rose::hash(o.path);
  h = rose::xor64(h);
  h ^= rose::hash(o.config);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct WorkspacePath
///////////////////////////////////////////////////////////////////
bool operator==(const WorkspacePath &lhs, const WorkspacePath &rhs) {
  return
    rose_parser_equals(lhs.path, rhs.path) ;
}

bool operator!=(const WorkspacePath &lhs, const WorkspacePath &rhs) {
  return
    !rose_parser_equals(lhs.path, rhs.path) ;
}

void rose::ecs::serialize(WorkspacePath &o, ISerializer &s) {
  if(s.node_begin("WorkspacePath", rose::hash("WorkspacePath"), &o)) {
    s.key("path");
    serialize(o.path, s, std::strlen(o.path));
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(WorkspacePath &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("path"):
        deserialize(o.path, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const WorkspacePath &o) {
  rose::hash_value h = rose::hash(o.path);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct Workspace
///////////////////////////////////////////////////////////////////
bool operator==(const Workspace &lhs, const Workspace &rhs) {
  return
    rose_parser_equals(lhs.path, rhs.path) &&
    rose_parser_equals(lhs.subsystems, rhs.subsystems) ;
}

bool operator!=(const Workspace &lhs, const Workspace &rhs) {
  return
    !rose_parser_equals(lhs.path, rhs.path) ||
    !rose_parser_equals(lhs.subsystems, rhs.subsystems) ;
}

void rose::ecs::serialize(Workspace &o, ISerializer &s) {
  if(s.node_begin("Workspace", rose::hash("Workspace"), &o)) {
    s.key("path");
    serialize(o.path, s);
    s.key("subsystems");
    serialize(o.subsystems, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(Workspace &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("path"):
        deserialize(o.path, s);
        break;
      case rose::hash("subsystems"):
        deserialize(o.subsystems, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const Workspace &o) {
  rose::hash_value h = rose::hash(o.path);
  h = rose::xor64(h);
  h ^= rose::hash(o.subsystems);
  return h;
}
///////////////////////////////////////////////////////////////////
//  struct WorkspaceConfig
///////////////////////////////////////////////////////////////////
bool operator==(const WorkspaceConfig &lhs, const WorkspaceConfig &rhs) {
  return
    rose_parser_equals(lhs.workspaces, rhs.workspaces) ;
}

bool operator!=(const WorkspaceConfig &lhs, const WorkspaceConfig &rhs) {
  return
    !rose_parser_equals(lhs.workspaces, rhs.workspaces) ;
}

void rose::ecs::serialize(WorkspaceConfig &o, ISerializer &s) {
  if(s.node_begin("WorkspaceConfig", rose::hash("WorkspaceConfig"), &o)) {
    s.key("workspaces");
    serialize(o.workspaces, s);
    s.node_end();
  }
  s.end();
}

void rose::ecs::deserialize(WorkspaceConfig &o, IDeserializer &s) {
  //implement me
  //construct_defaults(o);

  while (s.next_key()) {
    switch (s.hash_key()) {
      case rose::hash("workspaces"):
        deserialize(o.workspaces, s);
        break;
      default: s.skip_key(); break;
    }
  }
}

rose::hash_value rose::hash(const WorkspaceConfig &o) {
  rose::hash_value h = rose::hash(o.workspaces);
  return h;
}

#endif
