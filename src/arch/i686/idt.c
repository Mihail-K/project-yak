#include "assert.h"
#include "idt.h"

typedef struct __attribute__((packed)) {
    uint16_t size;
    uint32_t offset;
} IDTPointer;

typedef struct __attribute__((packed)) {
    uint16_t offset_0;
    uint16_t selector;
    uint8_t  zero;
    uint8_t  type  : 4;
    uint8_t  flags : 4;
    uint16_t offset_1;
} IDTEntry;

IDTPointer idtr;
IDTEntry idt[IDT_SIZE];
extern idt_isrptr_t isr_handlers[IDT_SIZE];

static IDTEntry _idt_create_entry(idt_isrptr_t isr_ptr, uint16_t selector, IDTType type, uint8_t flags)
{
    IDTEntry entry;

    entry.offset_0 =  ((uint32_t) isr_ptr)        & 0xFFFF;
    entry.offset_1 = (((uint32_t) isr_ptr) >> 16) & 0xFFFF;

    entry.selector = selector;
    entry.zero     = 0x00;
    entry.flags    = flags & 0x0F;
    entry.type     = type  & 0x0F;

    return entry;
}

static void _idt_populate_handlers(void)
{
    for (unsigned i = 0; i < IDT_SIZE; i++)
    {
        idt_set_entry(i, isr_handlers[i], 0x08, INTERRUPT_32BIT, IDT_FLAG_PRESENT | IDT_PRIVILEGE(0));
    }
}

static void _idt_load_idtr(void)
{
    idtr.size   = sizeof(idt) - 1;
    idtr.offset = (uint32_t) idt;

    asm volatile ("lidt (idtr)");
}

void idt_install(void)
{
    _idt_populate_handlers();
    _idt_load_idtr();
}

void idt_set_entry(uint8_t index, idt_isrptr_t isr_ptr, uint16_t selector, IDTType type, uint8_t flags)
{
    // ISR should be in Kernel space.
    assert((uintptr_t) isr_ptr >= 0xC0000000);

    idt[index] = _idt_create_entry(isr_ptr, selector, type, flags);
}
