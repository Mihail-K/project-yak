#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdbool.h>
#include <stdint.h>

typedef uintptr_t paddr_t;
typedef uintptr_t vaddr_t;

paddr_t paging_convert_to_physical(vaddr_t virtual_addr);
vaddr_t paging_convert_to_virtual(paddr_t physical_addr);

// Determines whether a virtual address is mapped.
bool paging_is_address_mapped(vaddr_t virtual_addr);

// Maps a given physical page to a virtual page.
// If the virtual page was previously mapped, returns the previous physical page.
paddr_t paging_map_page(paddr_t physical_page, vaddr_t virtual_page, uint8_t flags);

// Unmaps the page at the requested virtual page.
// The previous physical mapping is returned.
paddr_t paging_unmap_page(vaddr_t virtual_page);

void paging_install(void);

#endif
