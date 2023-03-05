#pragma once

namespace rose::test {
  struct TestContext {
    const char * title;
    const char * file;
    int line;
    virtual void check(bool, const char * expr, int testline) = 0;
  };

  typedef void (*fp_test_callback)(TestContext &);

  struct TestFactory {
    virtual ~TestFactory() {}
    virtual void RegisterClass(fp_test_callback callback, const char * title, const char* file, int line) = 0;
  };

}
extern rose::test::TestFactory * g_TestFactory;

#define UNIQUE_STRUCT_NAME TEST ## suffix ## _ ## __LINE__

#define CREATE_TEST(TITLE)                                                                 \
namespace {                                                                                \
  struct UNIQUE_STRUCT_NAME {                                                             \
    static void test_callback(rose::test::TestContext & ctx);                              \
    UNIQUE_STRUCT_NAME () { g_TestFactory->RegisterClass(test_callback, TITLE, __FILE__, __LINE__); } \
  };                                                                                       \
}                                                                                          \
UNIQUE_STRUCT_NAME g_ ## UNIQUE_STRUCT_NAME; \
void UNIQUE_STRUCT_NAME ::test_callback(rose::test::TestContext & ctx)                                           \

#define rose_test_xstr(a) str(a)
#define rose_test_str(a) #a

#define CHECK(EXPR) ctx.check(!!(EXPR), rose_test_str(EXPR), __LINE__)

