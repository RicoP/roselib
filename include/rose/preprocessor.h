#pragma once

#ifdef _MSC_VER
#  define ROSE_EXTERNALS_BEGIN __pragma(warning(push, 0))
#  define ROSE_EXTERNALS_END   __pragma(warning(pop))
#else
#  define ROSE_EXTERNALS_BEGIN
#  define ROSE_EXTERNALS_END
#endif

#define ROSE_MULTI_LINE_MACRO_BEGIN do {
#ifdef _MSC_VER
#  define ROSE_MULTI_LINE_MACRO_END                                             \
    }                                 /* ---------------------------------- */ \
    __pragma(warning(push))           /* push single warning                */ \
    __pragma(warning(disable : 4127)) /* conditional expression is constant */ \
    while (0)                         /* ---------------------------------- */ \
    __pragma(warning(pop))
#else
#  define ROSE_MULTI_LINE_MACRO_END \
    }                              \
    while (0)
#endif

// string helper
#define _ROSE_STRINGIFY(x) #x
#define ROSE_STRINGIFY(x) _ROSE_STRINGIFY(x)

// expands to something like "file.cpp:42"
#define ROSE_FILE_LINE __FILE__ ":" ROSE_STRINGIFY(__LINE__)

#define ROSE_UNUSED(VALUE) ((void)(VALUE))
