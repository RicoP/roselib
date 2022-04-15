#pragma once

#include <vector>

#include <components/path.h>

namespace rose {
namespace ecs {  
//@Flag
enum class SubsystemConfig : int {
  NONE = 0,
  Active = 1 << 0,
};

struct SubsystemPath {
  //@String
  path path;
  SubsystemConfig config = SubsystemConfig::NONE;
};

struct Workspace {
  std::vector<SubsystemPath> subsystems;

  //@String
  char console_filter[128] = "";
};
}
}
