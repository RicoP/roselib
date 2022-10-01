#include <utility>
#include <rose/owned.h>
#include <catch2/catch.hpp>

static size_t total_ = 0;

struct BigObject {
  char data[1024] = "";
  int value = 0;

  // https://stackoverflow.com/a/7097793
  BigObject() { ++total_; }
  BigObject(int val) : value(val) { ++total_; }
  BigObject(const BigObject& obj) {
    if (this != &obj) ++total_;
  }
  ~BigObject() { --total_; }

  static size_t count() { return total_; }
};

bool takeBO(rose::owned<BigObject> opt, int compare) {
  if (opt.valid()) {
    return opt->value == compare;
  }
  return false;
}

rose::owned<BigObject> createBO(bool ok, int value) {
  if (ok) {
    rose::owned<BigObject> opt = new BigObject();
    opt->value = value;
    return opt;
  } else {
    return nullptr;
  }
}

TEST_CASE("Sanity Check", "[owned]") {
  REQUIRE(0 == BigObject::count());
  {
    BigObject big;
    REQUIRE(1 == BigObject::count());
  }
  REQUIRE(0 == BigObject::count());
}

TEST_CASE("Member access", "[owned]") {
  REQUIRE(0 == BigObject::count());
  {
    rose::owned<BigObject> opt = new BigObject();

    REQUIRE(1 == BigObject::count());
    REQUIRE(opt.valid());

    opt->value = 42;
    REQUIRE(opt->value == 42);
    REQUIRE((*opt).value == 42);
  }
  REQUIRE(0 == BigObject::count());
  {
    auto opt = createBO(true, 42);
    REQUIRE(opt.valid());
    REQUIRE(1 == BigObject::count());
    REQUIRE(opt->value == 42);
    REQUIRE((*opt).value == 42);
  }
  REQUIRE(0 == BigObject::count());
  {
    auto opt = createBO(false, 42);
    REQUIRE(!opt.valid());
    REQUIRE(opt == nullptr);
    REQUIRE(0 == BigObject::count());
  }
  REQUIRE(0 == BigObject::count());
}

TEST_CASE("use 1", "[owned]") {
  bool ok;
  REQUIRE(0 == BigObject::count());

  auto opt = createBO(true, 42);
  REQUIRE(1 == BigObject::count());
  REQUIRE(opt.valid());

  ok = takeBO(std::move(opt), 42);
  REQUIRE(ok);
  REQUIRE(opt == nullptr);
  REQUIRE(0 == BigObject::count());

  ok = takeBO(std::move(opt), 42);
  REQUIRE(!ok);
  REQUIRE(0 == BigObject::count());

  ok = takeBO(new BigObject(55), 55);
  REQUIRE(ok);
  REQUIRE(0 == BigObject::count());
  
  ok = takeBO(createBO(true, 66), 66);
  REQUIRE(ok);
  REQUIRE(0 == BigObject::count());
}

TEST_CASE("use 2", "[owned]") {
  {
    rose::owned<BigObject> opt = nullptr;
    REQUIRE(0 == BigObject::count());

    auto opt1 = createBO(true, 1001);
    REQUIRE(1 == BigObject::count());
    auto opt2 = createBO(true, 1002);
    REQUIRE(2 == BigObject::count());
    auto opt3 = createBO(true, 1003);
    REQUIRE(3 == BigObject::count());

    opt = std::move(opt1);
    REQUIRE(opt1 == nullptr);
    REQUIRE(3 == BigObject::count());
    REQUIRE(opt->value == 1001);

    opt = std::move(opt2);
    REQUIRE(opt2 == nullptr);
    REQUIRE(2 == BigObject::count());
    REQUIRE(opt->value == 1002);

    opt = std::move(opt3);
    REQUIRE(opt3 == nullptr);
    REQUIRE(1 == BigObject::count());
    REQUIRE(opt->value == 1003);

    REQUIRE(opt1 == nullptr);
    REQUIRE(opt2 == nullptr);
    REQUIRE(opt3 == nullptr);
    REQUIRE(opt != nullptr);

    opt = new BigObject();
    REQUIRE(1 == BigObject::count());

    opt.destroy();
    opt = new BigObject(1111);
    REQUIRE(1 == BigObject::count());
    REQUIRE(opt->value == 1111);
  }
  REQUIRE(0 == BigObject::count());
}

