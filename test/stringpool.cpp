#include <rose/stringpool.h>
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("String Pool Sanity Check", "[string pool]") {
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
