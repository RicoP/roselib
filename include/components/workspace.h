#pragma once

#include <vector>


//@Flag
enum class SubsystemConfig : int {
  NONE = 0,
  Active = 1 << 0,
};

struct SubsystemPath {
  //@String
  char path[64];
  SubsystemConfig config = SubsystemConfig::NONE;
};

struct WorkspacePath {
  //@String
  char path[260];
};

struct Workspace {
  WorkspacePath path;
  std::vector<SubsystemPath> subsystems;
};

struct WorkspaceConfig {
  std::vector<Workspace> workspaces;
};
