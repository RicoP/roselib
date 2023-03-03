#include <cstdint>
#include <cstddef>
#include <iterator>
#include <rose/assert.h>

namespace rose {
typedef std::int32_t utf8code;
constexpr utf8code utf8code_end = 0;
constexpr utf8code utf8code_invalid = 0xFFFD;

struct utf8walker {
  const char * head = nullptr;
  int remaining_bytes = 0;

  utf8code next() {
    //https://github.com/RandyGaul/cute_framework/blob/5f68097c836802daad208f2fcb85256ddd136745/src/cute_string.cpp#LL553C48-L553C57
    if(remaining_bytes == 0) {
      return utf8code_end;
    } 

    unsigned char c = *head++;
    remaining_bytes--;

    utf8code codepoint = 0;
    utf8code codepoint_min = 0;
    int extra_bytes = 0;
    if (c >= 0xF0)      { codepoint = c & 0x07; extra_bytes = 3; codepoint_min = 0x10000; }
    else if (c >= 0xE0) { codepoint = c & 0x0F; extra_bytes = 2; codepoint_min = 0x800; }
    else if (c >= 0xC0) { codepoint = c & 0x1F; extra_bytes = 1; codepoint_min = 0x80; }
    else if (c >= 0x80) { codepoint = utf8code_invalid; }
    else {
      //simple ansii character
      codepoint = c;
      if(codepoint == 0) {
        //We hit a ansii zero...
        if(remaining_bytes != 0) {
          //...but the tail doesn't end
          codepoint = utf8code_invalid; 
          head += remaining_bytes;
          remaining_bytes = 0;
        }
        return codepoint;
      }
    }

    if(extra_bytes > remaining_bytes) {
      //we would overflow
      head += remaining_bytes;
      remaining_bytes = 0;
      return utf8code_invalid;
    }

    while (extra_bytes--) {
      c = *head++;
      remaining_bytes--;
      if ((c & 0xC0) != 0x80) { 
        codepoint = utf8code_invalid;

        //TODO: should we keep iterating until extra hits zero?
        //      https://discord.com/channels/432009046833233930/876893754517241907/1081260978475368521
        break; 
      }
      codepoint = ((codepoint) << 6) | (c & 0x3F); 
    }

    if (codepoint < codepoint_min) return utf8code_invalid;
    return codepoint;
  }
};



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
  utf8walker span;

  utf8code peek() const {
    utf8walker copy = span;
    return copy.next();
  }

  utf8code increment() {
    return span.next();
  }

  utf8span() : span {} {}
  utf8span(const char * str, int length) : span { str, length } {}
  utf8walker begin() const { return span; }
  utf8walker end() const { return utf8walker { span.head + span.remaining_bytes, 0 }; }

  int length() const {
    int result = 0;
    utf8walker it1 = begin();

    for(;;) {
      auto code1 = it1.next();
      //TODO: should we handle codepoint utf8code_invalid differently?
      if(code1 == utf8code_end) return result;
      ++result;
    }
  }

  int compare(const utf8span & rhs) const { 
    utf8walker it1 = begin();
    utf8walker it2 = rhs.begin();

    for(;;) {
      auto code1 = it1.next();
      auto code2 = it2.next();
      if(code1 != code2) return code1 - code2;
      if(code1 == 0) return 0;
    }
  } 

  bool equals(const utf8span & rhs) const { 
    if(span.remaining_bytes != rhs.span.remaining_bytes) return false;
    return compare(rhs) == 0;
  }

  bool operator==(const utf8span & rhs) const { return equals(rhs); }
  bool operator!=(const utf8span & rhs) const { return !equals(rhs); }
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
      handle = factory->copy(handle); 
    }
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
    assert(this != &rhs);
    destroy();

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
  bool operator!=(const utf8 & rhs) const { return get() != rhs.get(); }
};

}
