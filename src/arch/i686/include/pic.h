#ifndef __ARCH_I686_PIC_H__
#define __ARCH_I686_PIC_H__

#include <stdbool.h>
#include <stdint.h>

#include "assert.h"

#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET  0x28

#define PIC_INTERRUPT_START (PIC_MASTER_OFFSET)
#define PIC_INTERRUPT_END   (PIC_MASTER_OFFSET + IRQ_MAX)

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

#define IRQ_MIN 0
#define IRQ_MAX 15

// Disables interrupts from the PIC.
static inline void pic_disable_interrupts(void)
{
    asm volatile ("cli");
}

// Enables interrupts from the PIC.
static inline void pic_enable_interrupts(void)
{
    asm volatile ("sti");
}

// Determines if an interrupt is an IRQ from the PIC.
static inline bool pic_interrupt_is_irq(uint8_t interrupt)
{
    return PIC_INTERRUPT_START <= interrupt && interrupt <= PIC_INTERRUPT_END;
}

// Converts an IRQ to its IDT interrupt number.
static inline uint8_t pic_irq_to_interrupt(IRQ irq)
{
    assert(irq >= IRQ_MIN);
    assert(irq <= IRQ_MAX);

    return irq + PIC_MASTER_OFFSET;
}

// Converts an IDT interrupt number to its IRQ.
static inline IRQ pic_interrupt_to_irq(uint8_t interrupt)
{
    assert(pic_interrupt_is_irq(interrupt));

    return interrupt - PIC_MASTER_OFFSET;
}

void pic_disable(void);
void pic_install(void);
void pic_send_eoi(IRQ irq);
void pic_toggle_irq(IRQ irq, bool enabled);

#endif
