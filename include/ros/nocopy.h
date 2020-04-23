#pragma once

namespace ros {

//helper class that prohibits copying of class
class nocopy {
  nocopy(nocopy const&) = delete;
  nocopy& operator=(nocopy const&) = delete;
};

}
