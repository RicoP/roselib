#include <cstdint>
#include <cstddef>
#include <iterator>
#include <rose/assert.h>

namespace rose {
typedef int utf8code;
constexpr utf8code utf8code_invalid = 0xFFFD;

struct SimpleSpan {
  const char * s = nullptr;
  int size = 0;
};


//https://github.com/RandyGaul/cute_framework/blob/5f68097c836802daad208f2fcb85256ddd136745/src/cute_string.cpp#LL553C48-L553C57
inline utf8code cf_decode_UTF8(SimpleSpan * span) {
  if(span->size == 0) {
    return 0;
  } 

  SimpleSpan end;
  end.s = span->s + span->size;
  end.size = 0;

  unsigned char c = *span->s++;
  span->size--;

  int extra = 0;
  int min = 0;
  int codepoint = 0;
  if (c >= 0xF0) { codepoint = c & 0x07; extra = 3; min = 0x10000; }
  else if (c >= 0xE0) { codepoint = c & 0x0F; extra = 2; min = 0x800; }
  else if (c >= 0xC0) { codepoint = c & 0x1F; extra = 1; min = 0x80; }
  else if (c >= 0x80) { codepoint = utf8code_invalid; }
  else codepoint = c;

  if(extra > span->size) {
    *span = end;
    return 0;
  }
  span->size -= extra;

  while (extra--) {
    c = *span->s++;
    if ((c & 0xC0) != 0x80) { codepoint = utf8code_invalid; break; }
    codepoint = ((codepoint) << 6) | (c & 0x3F);
  }
  if (codepoint < min) codepoint = utf8code_invalid;

  if(codepoint == 0 || codepoint == utf8code_invalid) *span = end;
  return codepoint;
}

/*
struct utf8iterator {
  const char * head;

  utf8iterator(const char * head_) : head(head_) {}

  // Required typedefs
  typedef std::ptrdiff_t difference_type;
  typedef char value_type;
  typedef const char* pointer;
  typedef const char& reference;
  typedef std::forward_iterator_tag iterator_category;

  void increment() {
    int bytes = 999;
    utf8code code = cf_decode_UTF8(head, &bytes);
    (void)(code);
    //TODO: check overflow
    head += bytes;
  }

  // Required member functions
  utf8iterator& operator++() {
    increment();
    return *this;
  }

  utf8iterator operator++(int) {
    utf8iterator copy = *this;
    increment();  
    return copy;
  }

  const reference operator*() const { return *head; }
  const pointer operator->() const { return head; }  
  
  bool operator==(utf8span rhs) const { return head == rhs.head && tail_in_bytes == rhs.tail_in_bytes; }
  bool operator!=(utf8span rhs) const { return !(*this == rhs); }
};
*/

struct utf8span {
  SimpleSpan span;

  utf8code peek() const {
    SimpleSpan copy = span;
    return cf_decode_UTF8(&copy);
  }

  utf8code increment() {
    return cf_decode_UTF8(&span);
  }

  utf8span() : span {} {}
  utf8span(const char * str, int length) : span { str, length } {}
  SimpleSpan begin() const { return span; }
  SimpleSpan end() const { return SimpleSpan { span.s + span.size, 0 }; }

  int length() const {
    int result = 0;
    SimpleSpan it1 = begin();

    for(;;) {
      auto code1 = cf_decode_UTF8(&it1);
      if(code1 == 0) return result;
      //TODO: Is it the right thing to return zero when the string contains a invalid byte order?
      if(code1 == utf8code_invalid) return 0;
      ++result;
    }
  }

  bool operator==(const utf8span & rhs) const { 
    if(this->span.size != rhs.span.size) return false;

    SimpleSpan it1 = begin();
    SimpleSpan it2 = rhs.begin();

    for(;;) {
      auto code1 = cf_decode_UTF8(&it1);
      auto code2 = cf_decode_UTF8(&it2);
      if(code1 != code2) return false;
      if(code1 == 0) return true;
      if(code1 == utf8code_invalid) return false;
    }
  }
  bool operator!=(const utf8span & rhs) const { return !(*this == rhs); }
};

//https://dev.to/totally_chase/implementing-functional-type-safe-polymorphism-in-c-10b9
struct utf8vfactory {
  void * context = nullptr;
  utf8span (* const fp_get     )(void *, int) = 0;
  int      (* const fp_copy    )(void *, int) = 0;
  int      (* const fp_make    )(void *, const char *) = 0;
  void     (* const fp_destroy )(void *, int) = 0;
  //int  (* const fp_append  )(void *, utf8span) = 0;

  utf8span get   (int handle) const { return fp_get(context, handle); }
  int      copy    (int handle) const { return fp_copy(context, handle); }
  int      make    (const char * string) const { return fp_make(context, string); }
  void     destroy (int handle) const { fp_destroy(context, handle); }
  //int    append  (utf8span span) { return fp_append(context, span); }
};

struct utf8 {
private:  
  union {
    const utf8vfactory * factory;
    const char * static_string;
  };
  //when <0 then static_string is active with a length of -handle
  int handle;

  bool is_static_string() const {
    return handle <= 0;
  }

  int static_string_length() const {
    assert(is_static_string());
    return -handle;
  }

  void destroy() {
    if(is_static_string()) return;
    if(factory) factory->destroy(handle);
    static_string = "";
    handle = 0;
  }

public:
  utf8() : static_string(""), handle(0) {}
  utf8(const utf8vfactory * factory_, int handle_) : factory(factory_), handle(handle_) {};
  utf8(const char * string_, int length_) : static_string(string_), handle(-length_) {};
  ~utf8() { destroy(); }

  template<int N>
  utf8(const char (&string_)[N]) : static_string(string_), handle(-(N-1)) {};

  utf8(const utf8 & rhs) {
    if(rhs.is_static_string()) {
      static_string = rhs.static_string;
      handle = rhs.handle;
    }
    else {
      factory = rhs.factory;
      handle = factory->copy(handle); }
    }
  utf8(utf8 && rhs) : factory(rhs.factory), handle(rhs.handle) { 
    if(rhs.is_static_string()) {
      static_string = rhs.static_string;
      handle = rhs.handle;
    }
    else {
      factory = rhs.factory;
      handle = rhs.handle;
    }

    rhs.static_string = "";
    rhs.handle = 0;
  }

  // Copy assignment operator
  utf8& operator=(const utf8& rhs) {
    if (this != &rhs) {
      // First destroy the current object's resources
      destroy();
      // Assign the factory and copy the handle
      factory = rhs.factory;
      handle = factory->copy(rhs.handle);
    }
    return *this;
  }

  // Move assignment operator
  utf8& operator=(utf8&& rhs) {
    if (this != &rhs) {
      // First destroy the current object's resources
      destroy();
      // Move the factory and handle
      factory = rhs.factory;
      handle = rhs.handle;
      // Set rhs to a valid state
      rhs.handle = 0;
      rhs.factory = nullptr;
    }
    return *this;
  }  
  
  utf8span get() const { 
    if(is_static_string()) return utf8span(static_string, static_string_length());
    return factory->get(handle); 
  }
  operator utf8span() const { return get(); }
  utf8span operator->() const { return get(); }
  int length() const { return get().length(); }

  /*
  utf8 append(utf8span span) { 
    int new_handle = factory->append(span);
    return utf8 { factory, new_handle };
  }

  utf8 operator+= (const utf8 & rhs) {
    return append(rhs);
  }

  utf8 operator+ (const utf8 & rhs) const { 
    utf8 lhs = *this;
    return lhs.append(rhs);
  }
  */

  bool operator==(const utf8 & rhs) const { return get() == rhs.get(); }
  bool operator!=(const utf8 & rhs) const { return !(*this == rhs); }
};

}
