#ifndef __ARCH_I686_PIC_H__
#define __ARCH_I686_PIC_H__

#include <stdint.h>

void pic_disable(void);
void pic_install(void);
void pic_send_eoi(uint8_t irq);

#endif
