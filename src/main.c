#include "console.h"
#include "dsl.h"

void kmain()
{
    console_writeln("Starting Kernel.");
    hang();
}
