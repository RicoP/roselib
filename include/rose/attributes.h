#pragma once

#include <initializer_list>

namespace rose {
namespace intern {
  struct attribute_t {
    //attribute_t(const attribute_t &) = delete;
  };

  struct attribute_flag_t {};
  struct field_attribute_flag_t : attribute_flag_t {};
  struct enum_attribute_flag_t : attribute_flag_t {};
  struct global_attribute_flag_t : attribute_flag_t {};
}  // namespace intern


// c-style string is null terminated. Only the part before null will be serialized.
constexpr intern::field_attribute_flag_t cstring_null;
// c-style string will be treated as data. The entire string will be serialized.
constexpr intern::field_attribute_flag_t cstring_data;
// Field will not be serialized.
constexpr intern::field_attribute_flag_t ignore;
// Enum class is treated as flags, meaning it has |= &= bit flag operators.
constexpr intern::enum_attribute_flag_t flag;
// Parse the next multiline comment like it's regular code.
constexpr intern::global_attribute_flag_t imposter;

}  // namespace rose

// define those outside of the rose namespace for convinience

// Attribute for field members.
struct field_a : rose::intern::attribute_t {
  field_a(const std::initializer_list<rose::intern::field_attribute_flag_t> &);
};
// Attribute for enum classes.
struct enum_a : rose::intern::attribute_t {
  enum_a(const std::initializer_list<rose::intern::field_attribute_flag_t> &);
};
// Attribute for global namespaces (like comments).
struct global_a : rose::intern::attribute_t {
  global_a(const std::initializer_list<rose::intern::field_attribute_flag_t> &);
};
//meta attrbibute to set extra parameters
struct meta_a {
  //show field only when condition is met.
  const char *condition;
};

#define $(...)

$(global_a(rose::imposter))
$(field_a(rose::cstring_data), meta_a{.condition = "1 < 2"})
$(field_a(rose::cstring_null))
$(field_a(rose::ignore), meta_a{.condition = "foo()"})
$(enum_a(rose::flag), meta_a{.condition = "bFlag == true")
