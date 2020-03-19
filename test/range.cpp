#include <ros/range.h>

#include <iostream>

int main() {
  for (auto i : ros::Range(3, 10)) {
    std::cout << i << "\n";
  }

  for (auto i : ros::Range(3.14, 4.0, 0.1)) {
    std::cout << i << "\n";
  }

  return 0;
}
