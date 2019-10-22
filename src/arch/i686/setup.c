#include "console.h"
#include "gdt.h"

void ksetup()
{
    console_clear();
    console_writeln("Console ready.");

    gdt_install();
    console_writeln("GDT Ready.");
}
