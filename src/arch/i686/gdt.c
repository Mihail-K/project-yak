#include "gdt.h"

#define GDT_NULL        0
#define GDT_CODE_KERNEL GDT_DESCTYPE(1) | GDT_PRES(1) | GDT_SAVL(0) | \
                        GDT_LONG(0)     | GDT_SIZE(1) | GDT_GRAN(1) | \
                        GDT_PRIV(0)     | GDT_CODE_EXRD
#define GDT_DATA_KERNEL GDT_DESCTYPE(1) | GDT_PRES(1) | GDT_SAVL(0) | \
                        GDT_LONG(0)     | GDT_SIZE(1) | GDT_GRAN(1) | \
                        GDT_PRIV(0)     | GDT_DATA_RDWR

#pragma pack(push, 1)
typedef struct {
    uint16_t size;
    uint32_t offset;
} GDTDescriptor;

typedef struct {
    uint16_t limit_0;
    uint16_t base_0;
    uint8_t  base_1;
    uint8_t  access;
    uint8_t  limit_1 : 4;
    uint8_t  flags   : 4;
    uint8_t  base_2;
} GDTEntry;
#pragma pack(pop)

GDTDescriptor gdtr;
GDTEntry gdt[3];

static GDTEntry _gdt_create_entry(uint32_t base, uint32_t limit, uint16_t flags)
{
    GDTEntry entry;

    entry.base_0 =  base        & 0xFFFF;
    entry.base_1 = (base >> 16) & 0x00FF;
    entry.base_2 = (base >> 24) & 0x00FF;

    entry.limit_0 =  limit        & 0xFFFF;
    entry.limit_1 = (limit >> 16) & 0x000F;

    entry.flags  = (flags >> 12) & 0x0F;
    entry.access =  flags        & 0xFF;

    return entry;
}

static void _gdt_initialize_default(void)
{
    gdt_set_entry(0, 0x00000000, 0x00000000, GDT_NULL);
    gdt_set_entry(1, 0x00000000, 0xFFFFFFFF, GDT_CODE_KERNEL);
    gdt_set_entry(2, 0x00000000, 0xFFFFFFFF, GDT_DATA_KERNEL);
}

static void _gdt_load_gdtr(void)
{
    gdtr.size   = sizeof(gdt);
    gdtr.offset = (uint32_t) gdt;

    asm volatile ("lgdt (gdtr)");
}

void gdt_install(void)
{
    _gdt_initialize_default();
    _gdt_load_gdtr();

    gdt_reload();
}

void gdt_reload()
{
    asm volatile
    (
        "ljmp $0x08, $.i686_lgdt_jump \n"
        ".i686_lgdt_jump: \n"
        "movw $0x10, %ax \n"
        "movw %ax,   %ds \n"
        "movw %ax,   %es \n"
        "movw %ax,   %fs \n"
        "movw %ax,   %gs \n"
        "movw %ax,   %ss \n"
    );
}

void gdt_set_entry(uint8_t index, uint32_t base, uint32_t limit, uint16_t flags)
{
    gdt[index] = _gdt_create_entry(base, limit, flags);
}
