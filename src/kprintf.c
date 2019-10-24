#include <stdbool.h>
#include <stdint.h>

#include "console.h"
#include "kprintf.h"

static void kprint_signed(int32_t value, int base)
{
    static char* alphabet = "0123456789ABCDEF";

    if (value == 0 || base < 2 || base > 16)
    {
        console_putch('0');
        return;
    }

    char buffer[66];
    int  index  = 65;
    bool negate = false;

    if (value < 0)
    {
        value  = -value;
        negate = true;
    }

    // Null-terminate buffer.
    buffer[--index] = 0;

    while (value != 0)
    {
        buffer[--index] = alphabet[value % base];
        value /= base;
    }

    if (negate)
    {
        buffer[--index] = '-';
    }

    console_write(&buffer[index]);
}

static void kprint_unsigned(uint32_t value, int base)
{
    static char* alphabet = "0123456789ABCDEF";

    if (value == 0 || base < 2 || base > 16)
    {
        console_putch('0');
        return;
    }

    char buffer[66];
    int  index  = 65;

    // Null-terminate buffer.
    buffer[--index] = 0;

    while (value != 0)
    {
        buffer[--index] = alphabet[value % base];
        value /= base;
    }

    console_write(&buffer[index]);
}

void kprintf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    kvprintf(format, args);

    va_end(args);
}

void kvprintf(const char* format, va_list args)
{
    while (format && *format)
    {
        char ch = *format++;

        if (ch != '%')
        {
            console_putch(ch);
            continue;
        }

        ch = *format++;

        switch (ch)
        {
            case 'd':
            case 'i':
                kprint_signed(va_arg(args, int32_t), 10);
                break;

            case 'u':
                kprint_unsigned(va_arg(args, uint32_t), 10);
                break;

            case 'x':
                kprint_unsigned(va_arg(args, uint32_t), 16);
                break;

            case 's':
                console_write(va_arg(args, char*));
                break;

            case '%':
                console_putch('%');
                break;

            default:
                console_putch(ch);
                break;
        }
    }
}
