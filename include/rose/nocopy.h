#pragma once

//helper class that prohibits copying of object
struct RNoCopy {
  RNoCopy() = default;
  ~RNoCopy() = default;
  RNoCopy(const RNoCopy &) = delete;
  RNoCopy &operator=(const RNoCopy &) = delete;
};
