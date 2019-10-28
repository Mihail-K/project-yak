#include <stdint.h>

#include "assert.h"
#include "bitops.h"
#include "logger.h"
#include "paging.h"

typedef enum {
    PAGE_DIRECTORY_PRESENT       = 0,
    PAGE_DIRECTORY_READ_WRITE    = 1,
    PAGE_DIRECTORY_USER_ACCESS   = 2,
    PAGE_DIRECTORY_WRITE_THROUGH = 3,
    PAGE_DIRECTORY_CACHE_DISABLE = 4,
    PAGE_DIRECTORY_ACCESSED      = 5,
    PAGE_DIRECTORY_ZERO          = 6,
    PAGE_DIRECTORY_LARGE_PAGE    = 7,
    PAGE_DIRECTORY_IGNORED       = 8,
    PAGE_DIRECTORY_UNUSED_1      = 9,
    PAGE_DIRECTORY_UNUSED_2      = 10,
    PAGE_DIRECTORY_UNUSED_3      = 11
} PageDirectoryFlag;

typedef union __attribute__((packed)) {
    uint32_t value;
    struct
    {
        uint16_t flags   : 12;
        paddr_t  address : 20;
    };
    struct
    {
        uint8_t present : 1;
        uint8_t read_write : 1;
        uint8_t user_access : 1;
        uint8_t write_through : 1;
        uint8_t cache_disabled : 1;
        uint8_t accessed : 1;
        uint8_t zero : 1;
        uint8_t large_page : 1;
        uint8_t ignored : 1;
        uint8_t unused_1 : 1;
        uint8_t unused_2 : 1;
        uint8_t unused_3 : 1;
    };
} PageDirectoryEntry;

typedef union __attribute__((packed)) {
    uint32_t value;
    struct
    {
        uint16_t flags   : 12;
        paddr_t  address : 20;
    };
    struct
    {
        uint8_t present : 1;
        uint8_t read_write : 1;
        uint8_t user_access : 1;
        uint8_t write_through : 1;
        uint8_t cache_disabled : 1;
        uint8_t accessed : 1;
        uint8_t dirty : 1;
        uint8_t zero : 1;
        uint8_t global : 1;
        uint8_t unused_1 : 1;
        uint8_t unused_2 : 1;
        uint8_t unused_3 : 1;
    };
} PageTableEntry;

typedef PageDirectoryEntry* PageDirectory;
typedef uint32_t* page_table_t;

#define ACTIVE_PAGE_DIRECTORY_ADDRESS 0xFFFFF000
#define ACTIVE_PAGE_TABLE_ADDRESS     0xFFC00000

#define PAGE_MASK              0xFFFFF000
#define PAGE_OFFSET_MASK       (~PAGE_MASK)
#define LARGE_PAGE_MASK        0xFFC00000
#define LARGE_PAGE_OFFSET_MASK (~LARGE_PAGE_MASK)

#define PAGE_DIRECTORY_ENTRIES 1024
#define PAGE_TABLE_ENTRIES     1024

static PageDirectory _page_directory = (PageDirectory) ACTIVE_PAGE_DIRECTORY_ADDRESS;

static inline unsigned _paging_get_page_directory_index(vaddr_t virtual_addr)
{
    return virtual_addr >> 22;
}

static inline unsigned _paging_get_page_table_index(vaddr_t virtual_addr)
{
    return (virtual_addr >> 12) & 0x03FF;
}

static inline PageDirectoryEntry _paging_get_page_directory_entry_for_address(vaddr_t virtual_addr)
{
    unsigned directory_index = _paging_get_page_directory_index(virtual_addr);

    return _page_directory[directory_index];
}

static inline PageTableEntry _paging_get_page_table_entry_for_address(vaddr_t virtual_addr)
{
    unsigned directory_index = _paging_get_page_directory_index(virtual_addr);
    unsigned table_index     = _paging_get_page_table_index(virtual_addr);

    return *(PageTableEntry*)(ACTIVE_PAGE_TABLE_ADDRESS + (PAGE_DIRECTORY_ENTRIES * directory_index));
}

paddr_t paging_convert_to_physical(vaddr_t virtual_addr)
{
    PageDirectoryEntry directory_entry = _paging_get_page_directory_entry_for_address(virtual_addr);

    assert(directory_entry.present);

    if (directory_entry.large_page)
    {
        return (directory_entry.value & LARGE_PAGE_MASK) | (virtual_addr & LARGE_PAGE_OFFSET_MASK);
    }
    else
    {
        PageTableEntry table_entry = _paging_get_page_table_entry_for_address(virtual_addr);

        assert(table_entry.present);

        return (table_entry.value & PAGE_MASK) | (virtual_addr & PAGE_OFFSET_MASK);
    }
}

vaddr_t paging_convert_to_virtual(paddr_t physical_addr)
{
    return physical_addr + 0xC0000000; // TODO: Implement me.
}

void paging_install(void)
{
    assert(sizeof(PageDirectoryEntry) == sizeof(uint32_t));
    assert(paging_convert_to_physical(0xC00B8000) == 0xB8000);
}
