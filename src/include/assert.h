#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "dsl.h"
#include "logger.h"

#define assert(condition) _assert(condition, #condition, __func__, __FILE__, __LINE__)

static inline void _assert(int result, const char* condition, const char* function, const char* filename, unsigned line)
{
    if (!result)
    {
        fatal("Assertion failed: %s\n", condition);
        fatal("From %s() on %s:%d\n", __func__, __FILE__, __LINE__);
        hang();
    }
}

#endif
