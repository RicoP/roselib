#include <rose/hash.h>

#include <cassert>

int main() {
  rose::hash_value h = 42;

  rose::next(h);
  assert(h != 42);

  for (int i = 0; i != 1000000; ++i) {
    float f = rose::nextf(h);
    assert(f >= 0.0f && f < 1.0f);
  }

  char const* strings[] = {"Hello", "World", "Foo", "foo", "bar", 0};

  int c = 0;
  const char** string_iter = strings;
  while (*string_iter) {
    const char* s = *string_iter;
    switch (rose::hash(s)) {
      case rose::hash("Hello"): c++; break;
      case rose::hash("World"): c++; break;
      case rose::hash("Foo"): c++; break;
      case rose::hash("foo"): c++; break;
      case rose::hash("bar"): c++; break;
    }
    ++string_iter;
  }

  assert(c == 5);
  {
    char const* strings[] = {"Hello", "World", "Foo", "foo", "bar", 0};

    int i = 0;
    bool a = rose::hash(strings[i++]) == rose::hash("Hello");
    bool b = rose::hash(strings[i++]) == rose::hash("World");
    bool c = rose::hash(strings[i++]) == rose::hash("Foo");
    bool d = rose::hash(strings[i++]) == rose::hash("foo");
    bool e = rose::hash(strings[i++]) == rose::hash("bar");

    assert(a);
    assert(b);
    assert(c);
    assert(d);
    assert(e);
  }

  {
    rose::hash_value a = rose::hash_fnv("Skybox");
    rose::hash_value b = rose::hash_fnv("skybox");
    rose::hash_value c = rose::hash_fnv("Hero");
    rose::hash_value d = rose::hash_fnv("hero");

    assert(a ^ b != c ^ d);
  }

  rose::hash_value h1 = rose::hash((char)'a');
  rose::hash_value h2 = rose::hash(1.0);
  rose::hash_value h3 = rose::hash(1.0f);
  rose::hash_value h4 = rose::hash(0xCAFEBABE);
  rose::hash_value h5 = rose::hash(0xCAFEBABEULL);
  rose::hash_value h6 = rose::hash(0xCAFEBABELL);

  return 0;
}
