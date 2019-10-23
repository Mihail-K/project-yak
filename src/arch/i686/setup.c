#include "console.h"
#include "gdt.h"
#include "idt.h"
#include "kprintf.h"

void ksetup()
{
    console_clear();
    console_writeln("Console Ready.");

    gdt_install();
    console_writeln("GDT Ready.");

    idt_install();
    console_writeln("IDT Ready.");

    asm ("int $250");
}
