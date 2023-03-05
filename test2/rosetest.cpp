#include <rose/testing.h>
#include <vector>

bool g_ok = true;
int g_check_count = 0;
int g_check_success_count = 0;

struct TestContextImpl : rose::test::TestContext {
  rose::test::fp_test_callback callback;

  virtual void check(bool condition, const char * expr, int testline) override {
    ++g_check_count;
    if(condition) ++g_check_success_count;
    g_ok &= condition;
    if(!condition) {
        printf("Check failed: %s (in %s:%d) \n", expr, file, testline);
    }
  }
};

std::vector<TestContextImpl> tests;

struct TestFactoryImpl : rose::test::TestFactory {
  virtual void RegisterClass(rose::test::fp_test_callback callback, const char * title, const char* file, int line) {
    TestContextImpl test;
    test.title = title;
    test.file = file;
    test.line = line;
    test.callback = callback;
    tests.push_back(test);
  }
} impl;

rose::test::TestFactory* g_TestFactory = &impl;

#include <rose/utf8.h>

int main() {
    printf("Enter main \n");

    for(auto & test : tests) {
        printf("Execute test %s in file %s:%d \n", test.title, test.file, test.line);
        test.callback(test);
    }

    if(g_ok) {
        printf("All tests OK! \n");
    } else {
        printf("Tests Failed \n");
    }
    printf("%d/%d \n", g_check_success_count, g_check_count);

    return g_ok ? 0 : 1;
}