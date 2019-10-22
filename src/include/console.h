#ifndef __CONSOLE_H__
#define __CONSOLE_H__

void console_clear(void);

void console_putch(char ch);

void console_set_pos(unsigned xpos, unsigned ypos);

void console_write(char* ch);
void console_writeln(char* ch);

#endif
