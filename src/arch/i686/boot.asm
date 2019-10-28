extern ksetup
extern kmain

MB_ALIGN    equ 1 << 0
MB_MEMINFO  equ 1 << 1
MB_FLAGS    equ MB_ALIGN | MB_MEMINFO
MB_MAGIC    equ 0x1BADB002
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

PAGE_PRESENT   equ 1 << 0
PAGE_READWRITE equ 1 << 1
PAGE_LARGE     equ 1 << 7
VIRTUAL_OFFSET equ 0xC0000000

; Multiboot Header and Checksum
section .multiboot
align 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

; Kernel Entry (lower-half)
section .text_low
global _kstart_low:function
_kstart_low:
    cli

    ; Install Kernel Page Directory (physical address).
    mov ecx, (boot_page_directory - VIRTUAL_OFFSET)
    mov cr3, ecx

    ; Enable Large-Page extension.
    mov ecx, cr4
    or  ecx, 0x10
    mov cr4, ecx

    ; Enable Paging.
    mov ecx, cr0
    or  ecx, 0x80000000
    mov cr0, ecx

    lea ecx, [_kstart]
    jmp ecx

section .text
align 4
global _kstart:function
_kstart:
    ; Load kernel stack.
    mov esp, stack_top

    add ebx, VIRTUAL_OFFSET
    push ebx
    push eax

    ; Arch specific setup.
    call ksetup

    ; Kernel entry.
    call kmain

.khang:
    ; Hang if kernel exits.
    cli
    hlt
    jmp .khang
.kend:

; Kernel Page Directory
section .data
align 4096
boot_page_directory:
    ; Map first 4MB to physical offset 0.
    dd 0 | (PAGE_PRESENT | PAGE_READWRITE | PAGE_LARGE)
    times 768 - 1 dd 0
    ; Map memory at 3GB mark to physical offset 0.
    dd 0 | (PAGE_PRESENT | PAGE_READWRITE | PAGE_LARGE)
    times 1023 - 769 dd 0
    ; Map page directory into itself at end of memory.
    dd (boot_page_directory - VIRTUAL_OFFSET) + (PAGE_PRESENT | PAGE_READWRITE)

; Kernel stack (16KB)
section .bss
align 16
stack_bottom:
    resb 16_384
stack_top:
