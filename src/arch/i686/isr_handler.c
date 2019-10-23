#include "kprintf.h"

void isr_common_handler(unsigned interrupt, void* frame)
{
    kprintf("Interrupt: %d!\n", interrupt);

    while(1)
    {
        asm("hlt");
    }
}
