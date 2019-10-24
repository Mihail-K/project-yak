#include "assert.h"
#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "logger.h"
#include "multiboot.h"
#include "pic.h"

void ksetup(uint32_t magic, MultibootInfo* info)
{
    console_clear();
    debug("Console Ready.\n");

    // Validate multiboot magic number.
    assert(magic == MULTIBOOT_MAGIC);
    assert(multiboot_feature_available(info, MULTIBOOT_FEATURE_MMAP));

    if (multiboot_feature_available(info, MULTIBOOT_FEATURE_MEMORY))
    {
        uint32_t memory = info->mem_lower + info->mem_upper;

        info("Available Memory: %dMiB.\n", memory / 1024);
    }

    gdt_install();
    debug("GDT Ready.\n");

    idt_install();
    debug("IDT Ready.\n");

    pic_install();
    debug("PIC Ready.\n");

    pic_toggle_irq(IRQ_PIT, false);
    asm volatile ("sti");
}
