#pragma once

namespace rose {

template <class T>
struct RangeIterator_ {
  typedef RangeIterator_<T> KLASS;

  T current;
  T end;
  T inc;

  RangeIterator_(T current_, T end_, T inc_) : current(current_), end(end_), inc(inc_) {}

  T operator*() const { return current; }
  bool operator==(const KLASS& other) const { return current >= other.end; }
  bool operator!=(const KLASS& other) const { return !(*this == other); }

  KLASS operator++(int) {
    KLASS ret(current);
    current += inc;
    return ret;
  }

  KLASS& operator++() {
    current += inc;
    return *this;
  }
};

template <class T>
struct Range_ {
  typedef RangeIterator_<T> iterator;
  typedef const RangeIterator_<T> const_iterator;

  T from;
  T to;
  T inc;

  constexpr Range_(T from_, T to_, T inc_) : from(from_), to(to_), inc(inc_) {}
  constexpr iterator begin() { return RangeIterator_<T>(from, to, inc); }
  constexpr iterator end() { return RangeIterator_<T>(to, to, inc); }
  constexpr const_iterator begin() const { return RangeIterator_<T>(0, to, inc); }
  constexpr const_iterator end() const { return RangeIterator_<T>(to, to, inc); }
};

// template <size_t from, size_t to, size_t increment = 1>
// constexpr Range_<T> range = Range_<from, to, increment>();

template <class T>
Range_<T> range(T from, T to, T inc = 1) {
  return Range_<T>(from, to, inc);
}

}  // namespace rose
