#pragma once

#include <rose/unused.h>

#ifdef NDEBUG
#  ifdef assert
#    undef assert
#  endif
#  define assert rose::unused
#else
#include <cassert>
//TODO: replace assert with call that throws
#endif
