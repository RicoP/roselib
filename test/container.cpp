#include <rose/container.h>
#include <rose/event.h>
#include <rose/eventqueue.h>
#include <rose/typetraits.h>

#include <cassert>

struct Test1 {
  float x, y, z;
};

struct Test2 {
  int i, j, k;
  Test1 test1;
};

//We have to create the type_id type_traits by hand, normaly we would generate them with rose.parser
namespace rose {
template <>
struct type_id<Test1> {
  static inline rose::hash_value VALUE = rose::hash("Test1");
};

template <>
struct type_id<Test2> {
  static inline rose::hash_value VALUE = rose::hash("Test2");
};
}

/*
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


  //Event Queue
  rose::EventQueueContainer<64, 2> container;
  rose::EventQueue queue(container);

  for (int i = 0; i != 2; ++i) {
    assert(queue.begin() == queue.end());

    Test1 t1a{1.0f, 2.0f, 3.0f};
    Test2 t2a{4, 5, 6, t1a};
    queue.push_back(t2a);
    queue.push_back(t1a);

    assert(queue.count() == 2);

    for (auto event : queue) {
      if (const Test1 *p = event.get<Test1>()) {
        assert(p->x == 1);
        assert(p->y == 2);
        assert(p->z == 3);
      } else if (const Test2 *p = event.get<Test2>()) {
        assert(p->test1.x == 1);
        assert(p->test1.y == 2);
        assert(p->test1.z == 3);
      }
      if (Test1 *p = event.get_mutable<Test1>()) {
        assert(p->x == 1);
        assert(p->y == 2);
        assert(p->z == 3);
      } else if (Test2 *p = event.get_mutable<Test2>()) {
        assert(p->test1.x == 1);
        assert(p->test1.y == 2);
        assert(p->test1.z == 3);
      }
    }
    queue.clear();
  }
  puts("OK");
  return 0;
}

*/
