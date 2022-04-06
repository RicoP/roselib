#pragma once

//Basically the (void)(unused_value) pattern to keep the
//compiler quite about unused variables. Also a good 
//replacement for empty method macros like ASSERT in Release.
//    #define ASSERT(COND, MSG) rose::unused(COND, MSG)
//will guarantee the execution of the expression COND and MSG.
namespace rose {
template <class Thead>
void unused(const Thead & head) {
  (void)(head);
}

template <class Thead, class... Ttail>
void unused(const Thead & head, Ttail... args) {
  rose::unused(head);
  rose::unused(args...);
}
}  // namespace rose
