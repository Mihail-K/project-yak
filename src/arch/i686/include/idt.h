#ifndef __ARCH_I686_IDT_H__
#define __ARCH_I686_IDT_H__

#include <stdint.h>

#define IDT_SIZE 256

#define IDT_FLAG_PRESENT (1 << 3)
#define IDT_PRIVILEGE(x) (((x) & 0x03) << 1)
#define IDT_FLAG_STORAGE (1 << 0)

typedef void* const idt_isrptr_t;

typedef enum
{
    INTERRUPT_16BIT = 0b0110,
    INTERRUPT_32BIT = 0b1110,
    TASK_32BIT      = 0b0101,
    TRAP_16BIT      = 0b0111,
    TRAP_32BIT      = 0b1111
} IDTType;

void idt_install(void);
void idt_set_entry(uint8_t index, idt_isrptr_t isr_ptr, uint16_t selector, IDTType type, uint8_t flags);

#endif
