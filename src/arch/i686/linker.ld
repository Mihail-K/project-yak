ENTRY(_kstart_low)

PHYSICAL_START = 0x00100000;
VIRTUAL_OFFSET = 0xC0000000;

SECTIONS
{
    . = PHYSICAL_START + VIRTUAL_OFFSET;

    _kernel_start = .;

    .text ALIGN(4) : AT(ADDR(.text) - VIRTUAL_OFFSET)
    {
        *(.multiboot)
        *(.textlow)
        *(.text)
    }

    .rodata ALIGN(4) : AT(ADDR(.rodata) - VIRTUAL_OFFSET)
    {
        *(.rodata)
    }

    .data ALIGN(4K) : AT(ADDR(.data) - VIRTUAL_OFFSET)
    {
        *(.data)
    }

    .bss ALIGN(32) : AT(ADDR(.bss) - VIRTUAL_OFFSET)
    {
        *(COMMON)
        *(.bss)
    }

    _kernel_end = .;
}
