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
    int end = -1;
  };

  /// AAAAABBBBCCCC...
  std::vector<char> utf8pool;

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

  int handleCounter = 1;
  int newHandle() { return handleCounter++; }

  struct RefCountedStringPointer {
    struct StringPool* pool = nullptr;
    int handle = -1;

    // Ref counting stuff
    // https://www.chriswirz.com/software/refernce-counting-classes-in-c-plus-plus

    void RefPlusOne() { /*if(pool)*/ pool->handleToTuple(handle)->ref_count++; }
    void RefMinusOne() { if(pool) pool->handleToTuple(handle)->ref_count--; }

    RefCountedStringPointer() = delete;
    RefCountedStringPointer(StringPool* pool, int handle) : pool(pool), handle(handle) {}
    ~RefCountedStringPointer() { RefMinusOne();  }

    RefCountedStringPointer(const RefCountedStringPointer& rhs) : handle(rhs.handle), pool(rhs.pool) { RefPlusOne(); }
    RefCountedStringPointer(RefCountedStringPointer&& rhs) noexcept : handle(rhs.handle), pool(rhs.pool) { rhs.pool = nullptr; }

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
    int begin_byte_offset;  //>=0
    int end_byte_offset;  //<=0
  };

  explicit StringPool() { }

  StringPool(const StringPool&) = delete;
 
  std::size_t string_count_total() const { return this->indexRefTuples.size(); }
  std::size_t string_count_active() const {
    return std::count_if(indexRefTuples.begin(), indexRefTuples.end(), [](const auto& tuple) { return tuple.ref_count != 0; });
  }

  int reserve_bytes(int length) {
    auto current = utf8pool.size();
    utf8pool.resize(current + length);
    return (int)current;
  }

  // String creator
  StringView create_new(const char* str, int length) {
    //int length = std::strlen(str);
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
    return StringView{p, 0, 0};
  }

  template<size_t N>
  StringView create_new(const char (&str)[N]) {
    return create_new(str, N - 1);
  }
};
}

