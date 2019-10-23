#ifndef __ARCH_I686_IO_H__
#define __ARCH_I686_IO_H__

#include <stdint.h>

static inline uint8_t inb(uint16_t port)
{
    uint8_t value;

    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t value;

    asm volatile ("inw %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}

static inline uint32_t inl(uint16_t port)
{
    uint32_t value;

    asm volatile ("inl %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}

static inline void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}

static inline void outw(uint16_t port, uint16_t value)
{
    asm volatile ("outw %0, %1" :: "a"(value), "Nd"(port));
}

static inline void outl(uint16_t port, uint32_t value)
{
    asm volatile ("outl %0, %1" :: "a"(value), "Nd"(port));
}

static inline void io_wait(void)
{
    // Write a value to port 128. Forces the CPU to wait an IO cycle.
    // Port 128 is 'unused' (reserved for manufacturer diagnostics).
    outb(128, 0);
}

#endif
