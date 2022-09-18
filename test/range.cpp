#include <rose/range.h>

#include <iostream>

int main() {
  for (auto i : rose::range(3, 10)) {
    std::cout << i << "\n";
  }

  for (auto i : rose::range(3.14, 4.0, 0.1)) {
    std::cout << i << "\n";
  }

  return 0;
}
