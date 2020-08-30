#include <ros/container.h>

#include <cassert>

int main() {
  rose::Hashmap<16, const char *, long long> map;
  map.emplace_back("hello", 12);
  map.emplace_back("world", 24);
  map.emplace_back("Hallo", 2);
  map.emplace_back("Ballo", 42);

  assert(map["hello"] == 12);
  assert(map["world"] == 24);
  assert(map["Hallo"] == 2);
  assert(map["Ballo"] == 42);

  assert(map.getOrDefault("missing", -77) == -77);

  return 0;
}
