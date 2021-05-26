#pragma once

#include <rose/preprocessor.h>

ROSE_EXTERNALS_BEGIN
#include <inttypes.h>

#include <cstdio>
ROSE_EXTERNALS_END

namespace ros {
namespace intern {

  int format_single_value(char *dest, size_t size, int value);
  int format_single_value(char *dest, size_t size, unsigned int value);
  int format_single_value(char *dest, size_t size, float value);
  int format_single_value(char *dest, size_t size, double value);
  int format_single_value(char *dest, size_t size, long double value);
  int format_single_value(char *dest, size_t size, char value);  // not standard conform but the only sane way
  int format_single_value(char *dest, size_t size, char *value);
  int format_single_value(char *dest, size_t size, const char *value);
  // int format_single_value(char * dest, size_t size, wint_t value); //same as unsigned short int
  int format_single_value(char *dest, size_t size, wchar_t *value);
  int format_single_value(char *dest, size_t size, const wchar_t *value);

  int format_single_value(char *dest, size_t size, signed short int value);
  int format_single_value(char *dest, size_t size, unsigned short int value);

  int format_single_value(char *dest, size_t size, long int value);
  int format_single_value(char *dest, size_t size, unsigned long int value);

  int format_single_value(char *dest, size_t size, long long int value);
  int format_single_value(char *dest, size_t size, unsigned long long int value);

  // int format_single_value(char * dest, size_t size, intmax_t value); //same as signed long int
  // int format_single_value(char * dest, size_t size, uintmax_t value); //same as signed long int
  // int format_single_value(char * dest, size_t size, size_t value); //same as unsigned int
  // int format_single_value(char * dest, size_t size, ptrdiff_t value); //same as int

  int format_single_value(char *dest, size_t size, void *value);
  int format_single_value(char *dest, size_t size, const void *value);

  struct FormatData {
    char *dest;
    size_t size;
    const char *format;
  };

  bool format_intern_copyTillEnd(FormatData &data);
  bool format_intern_copyTillToken(FormatData &data);

  inline bool format_intern_print(FormatData &) { return true; }

  template <typename Head>
  bool format_intern_print(FormatData &data, const Head &value) {
    if (!format_intern_copyTillToken(data)) {
      return false;
    }

    int m = format_single_value(data.dest, data.size, value);
    if (m < 0) return false;
    data.dest += m;
    data.size -= m;

    return true;
  }

  template <typename Head, typename... Args>
  bool format_intern_print(FormatData &data, const Head &value, Args... args) {
    return format_intern_print(data, value) && format_intern_print(data, args...);
  }

  template <typename... Args>
  int format_impl(char *dest, size_t bufferSize, const char *format, Args... args) {
    FormatData data;
    data.dest = dest;
    data.size = bufferSize;
    data.format = format;

    bool ok = format_intern_print(data, args...);
    if (!ok) return -1;

    if (!format_intern_copyTillEnd(data)) {
      return -1;
    }

    return static_cast<int>(bufferSize - data.size) + 1;
  }
}  // namespace intern
}  // namespace ros

namespace ros {
namespace strings {

  template <typename... Args>
  int format(char *dest, size_t bufferSize, const char *format, Args... args) {
    return ros::intern::format_impl(dest, bufferSize, format, args...);
  }

  template <size_t SIZE, typename... Args>
  int format(char (&dest)[SIZE], const char *format, Args... args) {
    return ros::intern::format_impl(dest, SIZE, format, args...);
  }

}  // namespace strings
}  // namespace ros
