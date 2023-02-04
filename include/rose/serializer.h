#pragma once

#include <serializer/serializer.h>
#include <type_traits>

namespace rose {

template <class E>
struct BoolConvertible {
  E value;

  operator E() const {
    return value;
  }

  operator bool() const {
    return static_cast<std::underlying_type_t<E>>(value) != 0;
  }
};

}
