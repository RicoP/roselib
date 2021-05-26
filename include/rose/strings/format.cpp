#include "format.h"

#include <cassert>

template <class T, size_t SIZE>
constexpr size_t vectorLength(T (&)[SIZE]) {
  return SIZE;
}

#define FORMAT(TYPE, PREFIX, MODIFIER)                                        \
  int ros::intern::format_single_value(char *dest, size_t size, TYPE value) { \
    char formatter[] = "%" PREFIX MODIFIER;                                   \
    formatter[vectorLength(PREFIX) + 1] = 0;                                  \
    return snprintf(dest, size, formatter, value);                            \
  }

// FORMAT(int, "", "c") //for character, but noone uses int's for characters
// FORMAT(signed char,"hh", "di") //when a character should be handled as a integer. Do a typecast instead
// FORMAT(unsigned char,"hh", "di") //when a character should be handled as a integer. Do a typecast instead

FORMAT(int, "", "di")
FORMAT(unsigned int, "", "uoxX")
FORMAT(float, "", "fFeEgGaA")
FORMAT(double, "", "fFeEgGaA")
FORMAT(long double, "L", "fFeEgGaA")
FORMAT(char, "", "c")  // not standard conform but the only sane way
FORMAT(char *, "", "s")
FORMAT(const char *, "", "s")
// FORMAT(wint_t, "", "c") //same as unsigned short int
FORMAT(wchar_t *, "l", "s")
FORMAT(const wchar_t *, "l", "s")

FORMAT(signed short int, "h", "di")
FORMAT(unsigned short int, "h", "uoxX")

FORMAT(long int, "l", "di")
FORMAT(unsigned long int, "l", "uoxX")

FORMAT(long long int, "ll", "di")
FORMAT(unsigned long long int, "ll", "uoxX")

// FORMAT(intmax_t, "j", "di") //same as signed long int
// FORMAT(uintmax_t, "j", "uoxX") //same as signed long int

// FORMAT(size_t, "z", "di") //assume size_t is always unsigned
// FORMAT(size_t, "z", "uoxX") //same as unsigned int

// FORMAT(ptrdiff_t, "z", "di") //assume ptrdiff_t is always unsigned
// FORMAT(ptrdiff_t, "z", "uoxX") //same as int

// FORMAT(void *, "", "p") //no type conflict, but the output of printf("%p", voidp) differs from windows and linux

int ros::intern::format_single_value(char *dest, size_t size, const void *value) {
  static_assert(sizeof(size_t) == sizeof(void *), "size mismatch");

  union {
    size_t u_ui;
    const void *u_vp;
  };

  u_vp = value;
  return ros::intern::format_single_value(dest, size, u_ui);
}

int ros::intern::format_single_value(char *dest, size_t size, void *value) {
  const void *cv = value;
  return ros::intern::format_single_value(dest, size, cv);
}

bool ros::intern::format_intern_copyTillEnd(FormatData &data) {
  assert(data.dest);
  assert(data.format);

  while (*data.format) {
    if (data.size == 0) return false;

    if (*data.format == '%') {
      ++data.format;
      if (*data.format != '%') {
        return false;  // to many formatter
      }
    }

    *data.dest = *data.format;
    ++data.dest;
    ++data.format;
    --data.size;
  }

  if (data.size == 0) return false;
  *data.dest = 0;

  return true;
}

bool ros::intern::format_intern_copyTillToken(FormatData &data) {
  assert(data.dest);
  assert(data.format);

  for (;;) {
    if (data.size == 0) return false;

    bool copy = true;
    char c = *data.format;

    if (c == '%') {
      ++data.format;
      copy = *data.format == '%';
    }

    if (copy) {
      *data.dest = c;
      ++data.dest;
      --data.size;

      if (c == 0) return false;

      ++data.format;

      continue;
    }

    if (*data.format != '$') {
      return false;  // NOT supportet yet
    }

    ++data.format;  // skip the %$
    return true;
  }
}
