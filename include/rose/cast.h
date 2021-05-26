#pragma once

// When I am supposed to use static_cast for quite literally everything instead of
// the C cast then let me at least use a short syntax so I can read my own code.
template <class T, class U>
T $(const U& value) {
  return static_cast<T>(value);
}
