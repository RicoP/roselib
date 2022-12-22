#include <rose/stringpool.h>
#include <catch2/catch.hpp>
#include <utility>

TEST_CASE("String Pool Sanity Check", "[string pool]") {
  {
    rose::StringPool pool;

    REQUIRE(0 == pool.string_count_active());
    REQUIRE(0 == pool.string_count_total());
    {
      rose::StringView str(pool, u8"Hellö");
      REQUIRE(1 == pool.string_count_total());
      REQUIRE(1 == pool.string_count_active());

      auto iter = str.iterator();
      REQUIRE('H' == iter.next_codepoint());
      REQUIRE('e' == iter.next_codepoint());
      REQUIRE('l' == iter.next_codepoint());
      REQUIRE('l' == iter.next_codepoint());
      REQUIRE(0x00F6 == iter.next_codepoint());
      REQUIRE(0 == iter.next_codepoint());
    }
    REQUIRE(1 == pool.string_count_total());
    REQUIRE(0 == pool.string_count_active());
  }

  {
    rose::StringPool pool;

    REQUIRE(0 == pool.string_count_active());
    REQUIRE(0 == pool.string_count_total());
    {
      rose::StringView str1(pool, "Hello World 1");
      REQUIRE(1 == pool.string_count_total());
      REQUIRE(1 == pool.string_count_active());
      REQUIRE((str1 == "Hello World 1"));

      rose::StringView str2(pool, "Hello World 2");
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
