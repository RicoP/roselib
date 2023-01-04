#pragma once

#include <serializer/serializer.h>

template <class E, class BaseT>
struct BoolConvertible {
  E value;

  operator E() const {
    return value;
  }

  operator bool() const {
    return static_cast<BaseT>(value) != 0;
  }
};
