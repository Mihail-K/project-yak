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

    assert(magic == MULTIBOOT_MAGIC);
    assert(multiboot_feature_available(info, MULTIBOOT_FEATURE_MMAP));

    if (multiboot_feature_available(info, MULTIBOOT_FEATURE_MEMORY))
    {
        uint32_t memory = info->mem_lower + info->mem_upper;

        info("Available Memory: %dMiB.\n", memory / 1024);
    }

    MultibootMemoryMap* mmap = multiboot_get_memory_map(info);

    for (unsigned i = 0; i < multiboot_mmap_entries_count(info); i++)
    {
        debug("Base: %u\n", (uint32_t)(mmap[i].base_addr & 0xFFFFFFFF));
        debug("Len:  %u\n", (uint32_t)(mmap[i].length & 0xFFFFFFFF));
        debug("Type: %u\n", mmap[i].type);
    }

    gdt_install();
    debug("GDT Ready.\n");

    idt_install();
    debug("IDT Ready.\n");

    pic_install();
    debug("PIC Ready.\n");

    pic_toggle_irq(IRQ_PIT, false);
    pic_enable_interrupts();
}
