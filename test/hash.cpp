#include <ros/hash.h>

#include <cassert>

int main() {
  ros::hash_value h = 42;

  ros::next(h);
  assert(h != 42);

  for (int i = 0; i != 1000000; ++i) {
    float f = ros::nextf(h);
    assert(f >= 0.0f && f < 1.0f);
  }

  char const* strings[] = {"Hello", "World", "Foo", "foo", "bar", 0};

  int c = 0;
  const char** string_iter = strings;
  while (*string_iter) {
    const char* s = *string_iter;
    switch (ros::hash(s)) {
      case ros::hash("Hello"):
        c++;
        break;
      case ros::hash("World"):
        c++;
        break;
      case ros::hash("Foo"):
        c++;
        break;
      case ros::hash("foo"):
        c++;
        break;
      case ros::hash("bar"):
        c++;
        break;
    }
    ++string_iter;
  }

  assert(c == 5);

  ros::hash_value h1 = ros::hash((char)'a');
  ros::hash_value h2 = ros::hash(1.0);
  ros::hash_value h3 = ros::hash(1.0f);
  ros::hash_value h4 = ros::hash(0xCAFEBABE);
  ros::hash_value h5 = ros::hash(0xCAFEBABEULL);
  ros::hash_value h6 = ros::hash(0xCAFEBABELL);

  return 0;
}
