#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE( "Faketest", "[say_hello]" ) {
    //TODO: is this possible without creating a new test?
    std::cout << "Test created on the " << __DATE__ << " at " << __TIME__ << std::endl;
}

#define ROSE_FORMAT_IMPL
#define ROSE_FORMAT_TEST
#include <rose/format.h>