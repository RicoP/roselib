#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch2/catch.hpp>

#include <rose/testing.h>
rose::test::TestFactory* g_TestFactory = nullptr;