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
      case ros::hash("Hello"): c++; break;
      case ros::hash("World"): c++; break;
      case ros::hash("Foo"): c++; break;
      case ros::hash("foo"): c++; break;
      case ros::hash("bar"): c++; break;
    }
    ++string_iter;
  }

  assert(c == 5);
  {
    char const* strings[] = {"Hello", "World", "Foo", "foo", "bar", 0};

    int i = 0;
    bool a = ros::hash(strings[i++]) == ros::hash("Hello");
    bool b = ros::hash(strings[i++]) == ros::hash("World");
    bool c = ros::hash(strings[i++]) == ros::hash("Foo");
    bool d = ros::hash(strings[i++]) == ros::hash("foo");
    bool e = ros::hash(strings[i++]) == ros::hash("bar");

    assert(a);
    assert(b);
    assert(c);
    assert(d);
    assert(e);
  }

  {
    ros::hash_value a = ros::hash_fnv("Skybox");
    ros::hash_value b = ros::hash_fnv("skybox");
    ros::hash_value c = ros::hash_fnv("Hero");
    ros::hash_value d = ros::hash_fnv("hero");

    assert(a ^ b != c ^ d);
  }

  ros::hash_value h1 = ros::hash((char)'a');
  ros::hash_value h2 = ros::hash(1.0);
  ros::hash_value h3 = ros::hash(1.0f);
  ros::hash_value h4 = ros::hash(0xCAFEBABE);
  ros::hash_value h5 = ros::hash(0xCAFEBABEULL);
  ros::hash_value h6 = ros::hash(0xCAFEBABELL);

  return 0;
}
