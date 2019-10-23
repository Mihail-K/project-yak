#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "dsl.h"
#include "logger.h"

#define assert(condition) \
    if (!(condition)) \
    { \
        fatal("Assertion failed: %s\n", #condition); \
        fatal("From %s() on %s:%d\n", __func__, __FILE__, __LINE__); \
        hang(); \
    }

#endif
