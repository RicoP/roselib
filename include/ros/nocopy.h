#pragma once

namespace ros {

//helper class that prohibits copying of class
class nocopy {
 public:
  nocopy() {}
  ~nocopy() {}

 private:
  nocopy(const nocopy &) = delete;
  const nocopy &operator=(const nocopy &) = delete;
};

}
