#ifndef __MATH_H__
#define __MATH_H__

static inline unsigned umin(unsigned a, unsigned b)
{
    return a < b ? a : b;
}

static inline unsigned umax(unsigned a, unsigned b)
{
    return a > b ? a : b;
}

#endif
