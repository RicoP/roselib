#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char ** argv) {
  std::cout << "Test created on the " << __DATE__ << " at " << __TIME__ << "\n";
  return Catch::Session().run(argc, argv);
}

#define ROSE_FORMAT_IMPL
#define ROSE_FORMAT_TEST
#include <rose/printf.h>