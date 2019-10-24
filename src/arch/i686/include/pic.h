#ifndef __ARCH_I686_PIC_H__
#define __ARCH_I686_PIC_H__

#include <stdbool.h>
#include <stdint.h>

#define IRQ_MAX 15

typedef enum {
    IRQ_PIT             = 0,
    IRQ_KEYBOARD        = 1,
    IRQ_CASCADE         = 2,
    IRQ_COM2            = 3,
    IRQ_COM1            = 4,
    IRQ_LPT2            = 5,
    IRQ_FLOPPY          = 6,
    IRQ_LPT1            = 7,
    IRQ_CMOS            = 8,
    IRQ_FREE1           = 9,
    IRQ_FREE2           = 10,
    IRQ_FREE3           = 11,
    IRQ_PS2_MOUSE       = 12,
    IRQ_FPU             = 13,
    IRQ_PRIMARY_ATA     = 14,
    IRQ_SECONDARY_ATA   = 15
} IRQ;

void pic_disable(void);
void pic_install(void);
void pic_send_eoi(IRQ irq);
void pic_toggle_irq(IRQ irq, bool enabled);

#endif
