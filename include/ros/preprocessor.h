#pragma once

#ifdef _MSC_VER
#  define ROS_EXTERNALS_BEGIN __pragma(warning(push, 0))
#  define ROS_EXTERNALS_END   __pragma(warning(pop))
#else
#  define ROS_EXTERNALS_BEGIN
#  define ROS_EXTERNALS_END
#endif

#define ROS_MULTI_LINE_MACRO_BEGIN do {
#ifdef _MSC_VER
#  define ROS_MULTI_LINE_MACRO_END                                             \
    }                                 /* ---------------------------------- */ \
    __pragma(warning(push))           /* push single warning                */ \
    __pragma(warning(disable : 4127)) /* conditional expression is constant */ \
    while (0)                         /* ---------------------------------- */ \
    __pragma(warning(pop))
#else
#  define ROS_MULTI_LINE_MACRO_END \
    }                              \
    while (0)
#endif

// string helper
#define _ROS_STRINGIFY(x) #x
#define ROS_STRINGIFY(x) _ROS_STRINGIFY(x)

// expands to something like "file.cpp:42"
#define ROS_FILE_LINE __FILE__ ":" ROS_STRINGIFY(__LINE__)
