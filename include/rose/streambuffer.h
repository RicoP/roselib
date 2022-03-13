#pragma once

namespace rose {

struct StreamBuffer {
  static constexpr size_t buffer_size_max_default = 1024;
  size_t buffer_size_max = buffer_size_max_default;

  int cursor_line = 1;
  size_t buffer_head = 0;
  size_t buffer_size = 0;

  char buffer_internal[2 * buffer_size_max_default] = "";
  char* buffer = buffer_internal;

  const char* path = nullptr;
  FILE* file = nullptr;

  bool eof = false;

  ~StreamBuffer() { assert(file == nullptr); }

  bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

  bool contains(char c, const char* characters) {
    if (c == 0) return true;
    for (;;) {
      if (*characters == 0) return false;
      if (*characters == c) return true;
      ++characters;
    }
  }

  bool is_c_identifier(char c) {
    if (c >= '0' && c <= '9') return true;
    if (c >= 'A' && c <= 'A') return true;
    if (c >= 'a' && c <= 'z') return true;
    if (c == '_') return true;
    if (c == '$') return true;
    return false;
  }

  void load(const char* path_) {
    file = fopen(path_, "rb");
    path = path_;
    assert(file);
  }

  void load_mem(char* buf, size_t len) {
    assert(file == nullptr);
    buffer_size_max = len;
    buffer_size = len;
    buffer = buf;
    path = "<MEMORY>";
  }

  template <size_t N>
  void load_mem(char (&str)[N]) {
    load_mem(str, N);
  }

  void unload() {
    assert(file);
    fclose(file);
    file = nullptr;
  }

  char* begin() { return buffer + buffer_head; }
  char* end() { return buffer + buffer_head + buffer_size; }

  void shift_buffer() {
    if (buffer_head == 0) return;
    for (size_t i = 0; i != buffer_size; ++i) {
      buffer[i] = buffer[buffer_head + i];
    }
    buffer_head = 0;
  }

  void fetch() {
    if (buffer_size == 0) {
      buffer_head = 0;
    } else if (buffer_head >= buffer_size_max) {
      shift_buffer();
    }
    char* new_input_begin = end();
    assert(new_input_begin <= buffer + buffer_size_max);
    size_t count = fread(new_input_begin, 1, buffer_size_max, file);
    assert(count <= buffer_size_max);
    buffer_size += count;
    eof = count == 0;
    // replace tabs with spaces
    for (char* p = new_input_begin; p != end(); ++p)
      if (*p == '\t') *p = ' ';
  }

  char peek() {
    if (buffer_size == 0) {
      fetch();
    }
    if (eof) return 0;
    return buffer[buffer_head];
  }

  char get() {
    char c = peek();
    if (c == 0) return 0;
    if (c == '\n') {
      cursor_line++;
    }
    ++buffer_head;
    --buffer_size;

    return c;
  }

  void skip(size_t num) {
    if (buffer_size < num) {
      fetch();
    }
    assert(buffer_size >= num);
    for (size_t i = 0; i != num; ++i) {
      if (buffer[buffer_head] == '\n') cursor_line++;
      ++buffer_head;
    }
    buffer_size -= num;
  }

  void skip_ws() {
    using namespace rose::internal;
    while (is_whitespace(peek())) skip(1);
  }

  char sws_get() {
    skip_ws();
    return get();
  }

  char sws_peek() {
    skip_ws();
    return peek();
  }

  void skip_line() {
    for (;;) {
      char c = get();
      if (c == '\n' || eof) return;
    }
  }

  bool test(const char* str, size_t len) {
    skip_ws();
    assert(len < buffer_size_max);

    if (buffer_size < len) fetch();
    if (buffer_size < len) return false;

    const char* buf = begin();
    for (size_t i = 0; i != len; ++i) {
      if (buf[i] != str[i]) return false;
    }
    return true;
  }

  template <size_t N>
  bool test(const char (&str)[N]) {
    return test(str, N - 1);
  }

  bool test_and_skip(const char* str, size_t len) {
    if (test(str, len)) {
      assert(buffer_size >= len);
      buffer_head += len;
      buffer_size -= len;
      return true;
    }
    return false;
  }

  template <size_t N>
  bool test_and_skip(const char (&str)[N]) {
    return test_and_skip(str, N - 1);
  }

  void read_till(char* dst, size_t len, const char* terminator) {
    using namespace rose::internal;
    char* p = dst;
    for (;;) {
      char c = peek();
      if (contains(c, terminator)) {
        *p = 0;
        break;
      }
      skip(1);
      if (p != dst + len - 1) *(p++) = c;
    }
  }

  void skip_till_word(const char* word, size_t len) {
    while (!test(word, len)) skip(1);
  }

  template <size_t N>
  void skip_till_word(const char (&str)[N]) {
    skip_till_word(str, N - 1);
  }

  void skip_till_any(const char* terminator) {
    using namespace rose::internal;
    for (;;) {
      char c = peek();
      if (contains(c, terminator)) {
        break;
      }
      skip(1);
    }
  }

  bool skip_comment() {
    bool has_multi_comment = test_and_skip("/*");
    if (has_multi_comment) {
      skip_till_word("*/");
      skip(2);
      return true;
    }

    bool has_annotation = test("//@");
    if (has_annotation) return false;

    bool has_single_comment = test_and_skip("//");
    if (has_single_comment) {
      skip_line();
    }
    return has_single_comment;
  }

  bool test_annotation(char* dst, size_t len) {
    using namespace rose::internal;
    if (test_and_skip("//@")) {
      read_till(dst, len, " \n\r\t");
      skip_line();
      return true;
    }
    return false;
  }

  template <size_t N>
  bool test_annotation(char (&dst)[N]) {
    return test_annotation(dst, N);
  }

  void read_c_identifier(char* dst, size_t len) {
    using namespace rose::internal;
    char* p = dst;
    for (;;) {
      char c = peek();
      if (!is_c_identifier(c)) {
        *p = 0;
        break;
      }
      skip(1);
      if (p != dst + len - 1) *(p++) = c;
    }
  }

  void sws_read_c_identifier(char* dst, size_t len) {
    skip_ws();
    read_c_identifier(dst, len);
  }

  template <size_t N>
  void read_c_identifier(char (&dst)[N]) {
    read_c_identifier(dst, N);
  }

  template <size_t N>
  void sws_read_c_identifier(char (&dst)[N]) {
    sws_read_c_identifier(dst, N);
  }

  void sws_read_till(char* dst, size_t len, const char* terminator) {
    skip_ws();
    read_till(dst, len, terminator);
    ;
  }

  template <size_t N>
  void read_till(char (&dst)[N], const char* terminator) {
    read_till(dst, N, terminator);
  }

  template <size_t N>
  void sws_read_till(char (&dst)[N], const char* terminator) {
    sws_read_till(dst, N, terminator);
  }
};

}  // namespace rose
