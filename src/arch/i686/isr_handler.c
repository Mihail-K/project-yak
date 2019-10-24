#include "dsl.h"
#include "logger.h"
#include "pic.h"
#include "io.h"

void isr_common_handler(unsigned interrupt, void* frame)
{
    if (pic_interrupt_is_irq(interrupt))
    {
        IRQ irq = pic_interrupt_to_irq(interrupt);

        debug("IRQ: %d!\n", irq);
        pic_send_eoi(irq);

        if (irq == IRQ_KEYBOARD)
        {
            inb(0x60);
        }
    }
    else
    {
        debug("Interrupt: %d!\n", interrupt);
        hang();
    }
}
