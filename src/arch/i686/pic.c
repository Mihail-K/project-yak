#include "assert.h"
#include "io.h"
#include "pic.h"

#define PIC_MASTER_ADDRESS      0x20
#define PIC_SLAVE_ADDRESS       0xA0
#define PIC_MASTER_COMMAND_PORT (PIC_MASTER_ADDRESS + 0)
#define PIC_SLAVE_COMMAND_PORT  (PIC_SLAVE_ADDRESS  + 0)
#define PIC_MASTER_DATA_PORT    (PIC_MASTER_ADDRESS + 1)
#define PIC_SLAVE_DATA_PORT     (PIC_SLAVE_ADDRESS  + 1)
#define PIC_END_OF_INTERRUPT    0x20

#define PIC_MASTER_OFFSET 0x20
#define PIC_SLAVE_OFFSET  0x28

#define ICW1_ICW4	    0x01		/* ICW4 (not) needed */
#define ICW1_SINGLE	    0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	    0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	    0x10		/* Initialization - required! */

#define ICW4_8086	    0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	    0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	    0x10		/* Special fully nested (not) */

static void _pic_remap(uint8_t master_offset, uint8_t slave_offset)
{
    // Save IRQ masks before configuration.
    uint8_t master_mask = inb(PIC_MASTER_DATA_PORT);
    uint8_t slave_mask  = inb(PIC_SLAVE_DATA_PORT);

    // Start initialization sequence in cascade mode.
    outb(PIC_MASTER_COMMAND_PORT, ICW1_INIT | ICW1_ICW4);
    outb(PIC_SLAVE_COMMAND_PORT,  ICW1_INIT | ICW1_ICW4);
    io_wait();

    // Set IRQ vector offests.
    outb(PIC_MASTER_DATA_PORT, master_offset);
    outb(PIC_SLAVE_DATA_PORT,  slave_offset);
    io_wait();

    // Set Slave to cascade to Master.
    outb(PIC_MASTER_DATA_PORT, 4);
    outb(PIC_SLAVE_DATA_PORT,  2);
    io_wait();

    // Configure for 8086 mode.
    outb(PIC_MASTER_DATA_PORT, ICW4_8086);
    outb(PIC_SLAVE_DATA_PORT,  ICW4_8086);
    io_wait();

    // Restore saved masks.
    outb(PIC_MASTER_DATA_PORT, master_mask);
    outb(PIC_SLAVE_DATA_PORT,  slave_mask);
}

void pic_disable(void)
{
    // Mask all IRQs.
    outb(PIC_MASTER_DATA_PORT, 0xFF);
    outb(PIC_SLAVE_DATA_PORT,  0xFF);
}

void pic_install(void)
{
    _pic_remap(PIC_MASTER_OFFSET, PIC_SLAVE_OFFSET);
}

void pic_send_eoi(IRQ irq)
{
    if (irq >= 8)
    {
        // For IRQs from the slave chip,
        // It is necessary to notify both Master and Slave.
        outb(PIC_SLAVE_COMMAND_PORT, PIC_END_OF_INTERRUPT);
    }

    outb(PIC_MASTER_COMMAND_PORT, PIC_END_OF_INTERRUPT);
}

void pic_toggle_irq(IRQ irq, bool enabled)
{
    uint16_t port;
    uint8_t value;

    assert(irq <= IRQ_MAX);

    if (irq < 8)
    {
        port = PIC_MASTER_DATA_PORT;
    }
    else
    {
        port = PIC_SLAVE_DATA_PORT;
        irq -= 8;
    }

    value = inb(port);
    
    if (enabled)
    {
        value |=  (1 << irq);
    }
    else
    {
        value &= ~(1 << irq);
    }

    outb(port, value);    
}
