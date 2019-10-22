#include <stdint.h>

#include "console.h"
#include "dsl.h"
#include "gdt.h"

void kernel_setup()
{
    console_clear();
    console_writeln("Console ready.");

    gdt_install();
    console_writeln("GDT Ready.");

    hang();
}
