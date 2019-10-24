#ifndef __MULTIBOOT_H__
#define __MULTIBOOT_H__

#include <stdbool.h>
#include <stdint.h>

#include "bitops.h"
#include "paging.h"

#define MULTIBOOT_MAGIC 0x2BADB002

typedef enum {
    MULTIBOOT_FEATURE_MEMORY       = 0,
    MULTIBOOT_FEATURE_BOOT_DEVICE  = 1,
    MULTIBOOT_FEATURE_CMDLINE      = 2,
    MULTIBOOT_FEATURE_MODS         = 3,
    MULTIBOOT_FEATURE_AOUT_SYMS    = 4,
    MULTIBOOT_FEATURE_ELF_SYMS     = 5,
    MULTIBOOT_FEATURE_MMAP         = 6,
    MULTIBOOT_FEATURE_DRIVES       = 7,
    MULTIBOOT_FEATURE_CONFIG       = 8,
    MULTIBOOT_FEATURE_LOADER_NAME  = 9,
    MULTIBOOT_FEATURE_APM          = 10,
    MULTIBOOT_FEATURE_VBE          = 11,
    MULTIBOOT_FEATURE_FRAMEBUFFER  = 12
} MultibootFeature;

typedef struct __attribute__((packed)) {
    uint32_t vbe_config_info;
    uint32_t vbe_mode_info;
    uint16_t vbe_mode;
    uint16_t vbe_interface_seg;
    uint16_t vbe_interface_off;
    uint16_t vbe_interface_len;
} MultibootVBEInfo;

typedef struct __attribute__((packed)) {
    uint64_t framebuffer_addr;
    uint32_t framebuffer_pitch;
    uint32_t framebuffer_width;
    uint32_t framebuffer_height;
    uint8_t  framebuffer_bpp;
    uint8_t  framebuffer_type;
    uint8_t  color_info[5];
} MultibootFramebufferInfo;

typedef struct __attribute__((packed)) {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t cmdline;
    uint32_t mods_count;
    uint32_t mods_addr;
    uint32_t syms[4];
    uint32_t mmap_length;
    uint32_t mmap_addr;
    uint32_t drives_length;
    uint32_t drives_addr;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t apm_table;

    MultibootVBEInfo vbe;
    MultibootFramebufferInfo framebuffer;
} MultibootInfo;

typedef struct __attribute__((packed)) {
    uint32_t size;
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
} MultibootMemoryMap;

static inline MultibootMemoryMap* multiboot_get_memory_map(MultibootInfo* info)
{
    return (MultibootMemoryMap*) paging_convert_to_virtual(info->mmap_addr);
}

static inline unsigned multiboot_mmap_entries_count(MultibootInfo* info)
{
    return info->mmap_length / sizeof(MultibootMemoryMap);
}

static inline bool multiboot_feature_available(MultibootInfo* info, MultibootFeature feature)
{
    return get_bit(info->flags, feature);
}

#endif
