#pragma once

#include <vector>
#include <cstdint>
#include <algorithm>
#include <rose/assert.h>

namespace rose
{
struct StringPool {
  struct StringRange {
    int begin = -1;
    int byte_count = -1;
  };

  /// AAAAABBBBCCCC...
  char* utf8pool = nullptr;
  int poolSize = 0;
  int poolCapacity = 0;

  /// AAAAABBBBCCCC...
  /// ^    ^   ^   ...
  /// The last element points on the end of the pool memory,
  /// so ranges should always contain at least one element.
  std::vector<StringRange> ranges;


  struct IndexRefTuple {
    int ref_count;
    int indexInRange;
  };

  /// 03,  57, 92, ... 
  std::vector<IndexRefTuple> indexRefTuples;

  struct StringPoolHandle {
    int handle;
    int indexToTuple;
  };

  /// lookup Of Handle To Index to indexRefTuples
  std::vector<StringPoolHandle> handleLookup;

  IndexRefTuple * handleToTuple(int handle) {
    // TODO: use binary search https://stackoverflow.com/a/4242557
    const auto begin = handleLookup.begin();
    const auto end = handleLookup.end();
    const auto found = std::find_if(begin, end, [handle](StringPoolHandle h) { return h.handle == handle; });
    if (found == end) return nullptr;
    return &indexRefTuples[found->indexToTuple];
  }

  int handleCounter = 0;
  int handleMostRecent = 0; //not always guaranteed to be == with handleCounter
  int newHandle() { return handleMostRecent = ++handleCounter; }

  struct RefCountedStringPointer {
    struct StringPool* pool = nullptr;
    int handle = 0;

    // Ref counting stuff
    // https://www.chriswirz.com/software/refernce-counting-classes-in-c-plus-plus

    IndexRefTuple* getTuple() const { return pool->handleToTuple(handle); }
    StringRange& getRange() const { return pool->ranges[getTuple()->indexInRange]; }

    void RefPlusOne() { /*if(pool)*/ pool->handleToTuple(handle)->ref_count++; }
    void RefMinusOne() { if(pool) pool->handleToTuple(handle)->ref_count--; }

    RefCountedStringPointer() = delete;
    RefCountedStringPointer(StringPool* pool, int handle) : pool(pool), handle(handle) {}
    ~RefCountedStringPointer() { RefMinusOne();  }

    RefCountedStringPointer(const RefCountedStringPointer& rhs) : handle(rhs.handle), pool(rhs.pool) { RefPlusOne(); }
    RefCountedStringPointer(RefCountedStringPointer&& rhs) noexcept : handle(rhs.handle), pool(rhs.pool) { rhs.pool = nullptr; rhs.handle = 0; }

    RefCountedStringPointer& operator=(const RefCountedStringPointer& rhs) {
      RefMinusOne();
      handle = rhs.handle;
      pool = rhs.pool;
      RefPlusOne();
    }
    RefCountedStringPointer&& operator=(RefCountedStringPointer&& rhs) noexcept {
      if(pool != rhs.pool) RefMinusOne();
      handle = rhs.handle;
      pool = rhs.pool;
      rhs.pool = nullptr;
    }
  };

  struct StringView {
    RefCountedStringPointer pointer;
    int begin_byte_offset = 0;  //>=0
    int byte_count = 0;  // <= pointer->...->byte_count

    const char* raw_cstr() const { return pointer.pool->utf8pool + pointer.getRange().begin + begin_byte_offset; }

    StringView append(const StringView&);

    bool equal(const char* rhs) {
      const char* lhs = raw_cstr();
      const char* end = lhs + byte_count;
      for (;;) {
        if (lhs == end) return *rhs == 0;
        if (*lhs != *rhs) return false;
        lhs++;
        rhs++;
      }
    }

    bool operator==(const char* rhs) { return equal(rhs); }
    bool operator!=(const char* rhs) { return !equal(rhs); }
  };

  explicit StringPool() { }

  StringPool(const StringPool&) = delete;
 
  std::size_t string_count_total() const { return this->indexRefTuples.size(); }
  std::size_t string_count_active() const {
    return std::count_if(indexRefTuples.begin(), indexRefTuples.end(), [](const auto& tuple) { return tuple.ref_count != 0; });
  }

  int reserve_bytes(int length) {
    auto current = poolSize;
    if (poolSize + length <= poolCapacity) {
    } else {
      poolCapacity += length;
      //utf8pool.resize(current + length);
      utf8pool = reinterpret_cast<char*>(std::realloc(utf8pool, poolCapacity));
    }
    poolSize += length;
    return (int)current;
  }

  StringView create_undefined(char * & new_str, int length) {
    int begin = reserve_bytes(length);
    new_str = &utf8pool[0] + begin;

    int rangeIndex = (int)ranges.size();
    ranges.emplace_back(StringRange{begin, begin + length});

    int tupleIndex = (int)indexRefTuples.size();
    indexRefTuples.emplace_back(IndexRefTuple{1, rangeIndex});

    int handle = newHandle();
    handleLookup.emplace_back(StringPoolHandle{handle, tupleIndex});

    RefCountedStringPointer p(this, handle);
    return StringView{p, 0, length};
  }

  // String creator
  StringView create_new(const char* str, int length) {
    int begin = reserve_bytes(length);
    char* buffer_begin = &utf8pool[0] + begin;
    //TODO: Maybe check we don't have a zero character here?
    std::memcpy(buffer_begin, str, length);

    int rangeIndex = (int)ranges.size();
    ranges.emplace_back(StringRange {begin, begin + length});

    int tupleIndex = (int)indexRefTuples.size();
    indexRefTuples.emplace_back(IndexRefTuple{ 1, rangeIndex });

    int handle = newHandle();
    handleLookup.emplace_back(StringPoolHandle{handle, tupleIndex});

    RefCountedStringPointer p(this, handle);
    return StringView{p, 0, length};
  }

  template<size_t N>
  StringView create_new(const char (&str)[N]) {
    return create_new(str, N - 1);
  }

  StringView create_new(const char * str) {
    int length = (int)std::strlen(str);
    return create_new(str, length);
  }
};

StringPool::StringView StringPool::StringView::append(const StringPool::StringView& rhs) {
  bool last = pointer.handle == pointer.pool->handleMostRecent;

  if (last) {
    //we can just extent the existing memory.
    bool actuallyEndWithLastByte = pointer.getRange().byte_count - this->begin_byte_offset == byte_count;
    if (actuallyEndWithLastByte) {
      //TODO: Extend existing memory.
      //return *this;
    }
  }

  // Create new string
  char* buffer;
  auto new_view = pointer.pool->create_undefined(buffer, this->byte_count + rhs.byte_count);

  std::memcpy(buffer, &this->pointer.pool->utf8pool[this->pointer.getRange().begin], this->byte_count);
  buffer += this->byte_count;
  std::memcpy(buffer, &rhs.pointer.pool->utf8pool[rhs.pointer.getRange().begin], rhs.byte_count);
  return new_view;
}
}

