#include <rose/stringpool.h>
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("String Pool Sanity Check", "[string pool]") {
  {
    rose::StringPool pool;

    REQUIRE(0 == pool.string_count_active());
    REQUIRE(0 == pool.string_count_total());
    {
      auto str = pool.create_new("Hello World");
      REQUIRE(1 == pool.string_count_total());
      REQUIRE(1 == pool.string_count_active());
    }
    REQUIRE(1 == pool.string_count_total());
    REQUIRE(0 == pool.string_count_active());
  }

  {
    rose::StringPool pool;

    REQUIRE(0 == pool.string_count_active());
    REQUIRE(0 == pool.string_count_total());
    {
      auto str1 = pool.create_new("Hello World 1");
      REQUIRE(1 == pool.string_count_total());
      REQUIRE(1 == pool.string_count_active());
      REQUIRE((str1 == "Hello World 1"));

      auto str2 = pool.create_new("Hello World 2");
      REQUIRE(2 == pool.string_count_total());
      REQUIRE(2 == pool.string_count_active());
      REQUIRE((str2 == "Hello World 2"));

      auto str3 = str1.append(str2);
      REQUIRE(3 == pool.string_count_total());
      REQUIRE(3 == pool.string_count_active());

      REQUIRE((str3 == "Hello World 1Hello World 2"));
    }
    REQUIRE(3 == pool.string_count_total());
    REQUIRE(0 == pool.string_count_active());
  }
}
