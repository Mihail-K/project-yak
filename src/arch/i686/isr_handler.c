#include "dsl.h"
#include "logger.h"

void isr_common_handler(unsigned interrupt, void* frame)
{
    debug("Interrupt: %d!\n", interrupt);
    hang();
}
