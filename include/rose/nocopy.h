#pragma once

namespace rose {

//helper class that prohibits copying of object
struct nocopy {
  nocopy() = default;
  ~nocopy() = default;
  nocopy(const nocopy &) = delete;
  nocopy &operator=(const nocopy &) = delete;
};

}
