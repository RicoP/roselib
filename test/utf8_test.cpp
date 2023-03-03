#include <rose/utf8.h>
#include <vector>
#include <map>
#include <catch2/catch.hpp>
#include <utility>

static int handle_counter = 0;
static std::vector<char> mem_pool;
static std::map<int, rose::utf8span> ranges_pool;

static rose::utf8 make_new_utf8(rose::utf8vfactory * factory, const char * from, int length_in_bytes) {
    auto i = mem_pool.size();
    mem_pool.resize(i + length_in_bytes);
    char * dst = &mem_pool[i];
    std::memcpy(dst, from, length_in_bytes);
    rose::utf8span span(dst, length_in_bytes);
    handle_counter++;
    ranges_pool[handle_counter] = span;
    return rose::utf8(factory, handle_counter);
}

template<int N>
rose::utf8 make_new_utf8(rose::utf8vfactory * factory, const char (&from)[N]) {
    return make_new_utf8(factory, from, N-1);
}

static rose::utf8span factory_get(void *, int handle) {
    return ranges_pool[handle];
}

static int factory_copy(void *, int handle) {
    handle_counter++;
    ranges_pool[handle_counter] = ranges_pool[handle];
    return handle_counter;
}

static void factory_destroy(void *, int handle) {
    //leaves a hole in the pool
    ranges_pool.erase(handle);
}

//static rose::utf8vfactory s_factory;
static rose::utf8vfactory make_factory() {
    return rose::utf8vfactory {
        .fp_get     = factory_get,
        .fp_copy    = factory_copy,
        .fp_destroy = factory_destroy
    };
}

TEST_CASE("UTF8 Sanity Check", "[rose string]") {
    rose::utf8vfactory factory = make_factory();
    
    rose::utf8 s1 = make_new_utf8(&factory, "Hello");
    rose::utf8 s2 = "static";

    REQUIRE(5 == s1.length());
    REQUIRE(6 == s2.length());
    
    {
      auto it = s1.get();
      REQUIRE('H' == it.increment());
      REQUIRE('e' == it.increment());
      REQUIRE('l' == it.increment());
      REQUIRE('l' == it.increment());
      REQUIRE('o' == it.increment());
      REQUIRE(0 == it.increment());
    }

    {
      auto it = s2.get();
      REQUIRE('s' == it.increment());
      REQUIRE('t' == it.increment());
      REQUIRE('a' == it.increment());
      REQUIRE('t' == it.increment());
      REQUIRE('i' == it.increment());
      REQUIRE('c' == it.increment());
      REQUIRE(0 == it.increment());
    }

    REQUIRE(s1 == s1);
    REQUIRE(s2 == s2);
    REQUIRE(s1 != s2);

    char cbuff[] = "Hello";
    REQUIRE(s1 == cbuff);
    REQUIRE(s2 != cbuff);
    
    REQUIRE(s1 == "Hello");
    REQUIRE(s2 == "static");
    
    REQUIRE(s1 != "");
    REQUIRE(s2 != "");
}
