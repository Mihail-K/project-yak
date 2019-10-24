#include "paging.h"

paddr_t paging_convert_to_physical(vaddr_t virtual_addr)
{
    return virtual_addr - 0xC0000000; // TODO: Implement me.
}

vaddr_t paging_convert_to_virtual(paddr_t physical_addr)
{
    return physical_addr + 0xC0000000; // TODO: Implement me.
}
