#include <cstdint>
#include <cstddef>
#include <iterator>

namespace rose {
typedef int utf8code;

struct SimpleSpan {
  const char * s = nullptr;
  int size = 0;

  bool operator==(SimpleSpan rhs) const { return s == rhs.s && size == rhs.size; }
  bool operator!=(SimpleSpan rhs) const { return !(*this == rhs); }
};

//https://github.com/RandyGaul/cute_framework/blob/5f68097c836802daad208f2fcb85256ddd136745/src/cute_string.cpp#LL553C48-L553C57
inline utf8code cf_decode_UTF8(SimpleSpan * span)
{
  
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
  else if (c >= 0x80) { codepoint = 0xFFFD; }
  else codepoint = c;

  if(extra > span->size) {
    *span = end;
    return 0;
  }
  span->size -= extra;

  while (extra--) {
    c = *span->s++;
    if ((c & 0xC0) != 0x80) { codepoint = 0xFFFD; break; }
    codepoint = ((codepoint) << 6) | (c & 0x3F);
  }
  if (codepoint < min) codepoint = 0xFFFD;

  if(codepoint == 0 || codepoint == 0xFFFD) *span = end;
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
    auto my_end = end();
    for(auto current = begin(); current != my_end; cf_decode_UTF8(&current)) {
      ++result;
    }
    return result;
  }

  bool operator==(utf8span rhs) const { return span == rhs.span; }
  bool operator!=(utf8span rhs) const { return !(*this == rhs); }
};

//https://dev.to/totally_chase/implementing-functional-type-safe-polymorphism-in-c-10b9
struct utf8vfactory {
  void * context = nullptr;
  utf8span (* const fp_get   )(void *, int) = 0;
  int    (* const fp_copy    )(void *, int) = 0;
  void   (* const fp_destroy )(void *, int) = 0;
  //int  (* const fp_append  )(void *, utf8span) = 0;

  utf8span get   (int handle) const { return fp_get(context, handle); }
  int    copy  (int handle) const { return fp_copy(context, handle); }
  void   destroy (int handle) const { fp_destroy(context, handle); }
  //int  append  (utf8span span) { return fp_append(context, span); }
};

struct utf8 {
  const utf8vfactory * factory = nullptr;
  int handle = 0;

  utf8(const utf8vfactory * factory_, int handle_) : factory(factory_), handle(handle_) {};
  utf8(const utf8 & rhs) : factory(rhs.factory) {                       handle = factory->copy(handle); }
  utf8(utf8 && rhs) : factory(rhs.factory), handle(rhs.handle) { rhs.handle = 0; rhs.factory = nullptr; }
  ~utf8()          { if(factory) factory->destroy(handle);           handle = 0;     factory = nullptr; }

  utf8span get() const { return factory->get(handle); }
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
};

}
