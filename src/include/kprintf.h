#ifndef __KPRINTF_H__
#define __KPRINTF_H__

#include <stdarg.h>

void kprintf(const char* format, ...);
void kvprintf(const char* format, va_list args);

#endif
