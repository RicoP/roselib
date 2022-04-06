#pragma once

#include <vector>


//@Flag
enum class SubsystemConfig : int {
  NONE = 0,
  Active = 1 << 0,
};

struct SubsystemPath {
  //@String
  char path[64] = "";
  SubsystemConfig config = SubsystemConfig::NONE;
};

struct Workspace {
  std::vector<SubsystemPath> subsystems;

  //@String
  char console_filter[128] = "";
};
