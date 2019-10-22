#include <stdint.h>

#include "console.h"
#include "io.h"
#include "math.h"

#define CONSOLE_XMAX 80
#define CONSOLE_YMAX 25
#define CONSOLE_SIZE (CONSOLE_XMAX * CONSOLE_YMAX)

typedef struct
{
    uint8_t ch;
    uint8_t colour;
} Symbol;

static Symbol* _vram = (Symbol*) 0xC00B8000;
static unsigned _xpos = 0;
static unsigned _ypos = 0;

static inline unsigned _console_offset(void)
{
    return _xpos + _ypos * CONSOLE_XMAX;
}

static inline void _console_scroll(void)
{
    unsigned i = 0;

    for (; i < CONSOLE_SIZE - CONSOLE_XMAX; i++)
    {
        _vram[i] = _vram[i + CONSOLE_XMAX];
    }
    for (; i < CONSOLE_SIZE; i++)
    {
        _vram[i].ch = 0;
        _vram[i].colour = 0;
    }
}

static inline void _console_update_cursor(void)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(_console_offset() & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((_console_offset() >> 8) & 0xFF));
}

void console_clear(void)
{
    for (unsigned i = 0; i < CONSOLE_SIZE; i++)
    {
        _vram[i].ch = 0;
        _vram[i].colour = 0;
    }

    _xpos = 0;
    _ypos = 0;

    _console_update_cursor();
}

void console_putch(char ch)
{
    switch(ch)
    {
        case '\n':
            _xpos = 0;
            _ypos++;
            break;

        case '\t':
            _xpos += (4 - (_xpos % 4));
            break;

        default:
            _vram[_console_offset()].ch = ch;
            _vram[_console_offset()].colour = 0x07;
            _xpos++;
            break;
    }

    if (_xpos == CONSOLE_XMAX)
    {
        _xpos = 0;
        _ypos++;
    }

    if (_ypos == CONSOLE_YMAX)
    {
        _console_scroll();
        _ypos--;
    }

    _console_update_cursor();
}

void console_set_pos(unsigned xpos, unsigned ypos)
{
    _xpos = umin(xpos, CONSOLE_XMAX);
    _ypos = umin(ypos, CONSOLE_YMAX);

    _console_update_cursor();
}

void console_write(char* string)
{
    while (string && *string)
    {
        console_putch(*string++);
    }
}

void console_writeln(char* string)
{
    console_write(string);
    console_write("\n");
}
