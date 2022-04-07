namespace rose {
namespace intern {
  namespace format {

    struct rose_format_chain {
      struct format_value_formatter {
        const char* format;
        enum class type {
          unknown_type = 0,
          int_type,
          uint_type,
          long_type,
          ulong_type,
          float_type,
          double_type,
          string_type,
          pointer_type,
        };

        type value_type = type::unknown_type;

        union {
          int i;
          unsigned u;
          long l;
          unsigned long ul;
          float f;
          double d;
          const char* s;
          void* p;
        };

        format_value_formatter(const char* format, int i) : format(format), i(i), value_type(type::int_type) {}
        format_value_formatter(const char* format, unsigned u) : format(format), u(u), value_type(type::uint_type) {}
        format_value_formatter(const char* format, long l) : format(format), l(l), value_type(type::long_type) {}
        format_value_formatter(const char* format, unsigned long ul) : format(format), ul(ul), value_type(type::ulong_type) {}
        format_value_formatter(const char* format, float f) : format(format), f(f), value_type(type::float_type) {}
        format_value_formatter(const char* format, double d) : format(format), d(d), value_type(type::double_type) {}
        format_value_formatter(const char* format, const char* s) : format(format), s(s), value_type(type::string_type) {}
        format_value_formatter(const char* format, char* s) : format(format), s(s), value_type(type::string_type) {}
        format_value_formatter(const char* format, void* p) : format(format), p(p), value_type(type::pointer_type) {}

        format_value_formatter(int i) : format("%d"), i(i), value_type(type::int_type) {}
        format_value_formatter(unsigned u) : format("%u"), u(u), value_type(type::uint_type) {}
        format_value_formatter(long l) : format("%ld"), l(l), value_type(type::long_type) {}
        format_value_formatter(unsigned long ul) : format("%lu"), ul(ul), value_type(type::ulong_type) {}
        format_value_formatter(float f) : format("%g"), f(f), value_type(type::float_type) {}
        format_value_formatter(double d) : format("%g"), d(d), value_type(type::double_type) {}
        format_value_formatter(const char* s) : format("%s"), s(s), value_type(type::string_type) {}
        format_value_formatter(char* s) : format("%s"), s(s), value_type(type::string_type) {}
        format_value_formatter(void* p) : format("%p"), p(p), value_type(type::pointer_type) {}

        rose_format_chain print(rose_format_chain chain) const;
      };

      char* data;
      int begin;
      int size;

      /*
    rose_format_chain val(const char* str) {
      while (*str && begin != size) {
        data[begin] = *str;
        ++begin;
        ++str;
      }
      return *this;
    }
    rose_format_chain val(char* str) { return val((const char*)str); }
      */

      const char* end() {
        if (begin == size) {
          return nullptr;
        }
        data[begin] = 0;
        return data;
      }

      rose_format_chain val(format_value_formatter formatter) { return formatter.print(*this); }

      operator const char*() {
        const char* value = end();
        return value;
      }
    };
  }  // namespace format
}  // namespace intern

intern::format::rose_format_chain format(char* buffer, int size) {
  intern::format::rose_format_chain chain;
  chain.data = buffer;
  chain.begin = 0;
  chain.size = size;
  return chain;
}

template <size_t N>
intern::format::rose_format_chain format(char (&buffer)[N]) {
  return format(buffer, (int)N);
}
}  // namespace rose

#ifdef ROSE_FORMAT_IMPL
///////////////////////////////////////////////
// Implementation
///////////////////////////////////////////////

#include <cstdio>  // for snprintf
#  define FORMAT_VALUE(i)                                           \
    sz = snprintf(chain.data + chain.begin, chain.size, format, i); \
    if (sz <= 0 || sz > (chain.size - chain.begin)) {               \
      /*ERROR*/ chain.begin = chain.size;                           \
    } else {                                                        \
      chain.begin += sz;                                            \
    }                                                               \
    return chain

rose_format_chain rose::intern::format::rose_format_chain::format_value_formatter::print(rose_format_chain chain) const {
  int sz;
  const char* str = s;
  switch (value_type) {
    case type::string_type:
      while (*str && chain.begin != chain.size) {
        chain.data[chain.begin] = *str;
        ++chain.begin;
        ++str;
      }
      return chain;

    case type::int_type: FORMAT_VALUE(i);
    case type::uint_type: FORMAT_VALUE(u);
    case type::long_type: FORMAT_VALUE(l);
    case type::ulong_type: FORMAT_VALUE(ul);
    case type::float_type: FORMAT_VALUE(f);
    case type::double_type: FORMAT_VALUE(d);
    case type::pointer_type: FORMAT_VALUE(p);
    default: chain.begin = chain.size; return chain;
  }
}
#  undef FORMAT_VALUE

#endif

#ifdef ROSE_FORMAT_TEST
///////////////////////////////////////////////
// TEST
///////////////////////////////////////////////
#  include <string>

TEST_CASE("rose::format") {
  char str[256];

  REQUIRE("Hello World" == (std::string)(rose::format(str).val("Hello World").end()));
  REQUIRE("42" == (std::string)(rose::format(str).val(42).end()));
  REQUIRE("3.14" == (std::string)(rose::format(str).val(3.14).end()));
  REQUIRE("3.14" == (std::string)(rose::format(str).val(3.14f).end()));
  REQUIRE("        42" == (std::string)(rose::format(str).val({"%10d", 42}).end()));
  REQUIRE("0000000042" == (std::string)(rose::format(str).val({"%010d", 42}).end()));
}
#endif
