#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "logger.h"

void ksetup()
{
    console_clear();
    debug("Console Ready.\n");

    gdt_install();
    debug("GDT Ready.\n");

    idt_install();
    debug("IDT Ready.\n");

    asm ("int $250");
}
