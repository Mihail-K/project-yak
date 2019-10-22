MB_ALIGN    equ 1 << 0
MB_MEMINFO  equ 1 << 1
MB_FLAGS    equ MB_ALIGN | MB_MEMINFO
MB_MAGIC    equ 0x1BADB002
MB_CHECKSUM equ -(MB_MAGIC + MB_FLAGS)

; Multiboot Header and Checksum
section .multiboot
align 4
dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

; Kernel stack (16KB)
section .bss
align 16
stack_bottom:
    resb 16_384
stack_top:

section .text
global _kstart:function (_kstart.end - _kstart)
_kstart:
    ; Load kernel stack.
    mov esp, stack_top

    ; 
    extern kernel_setup
    call kernel_setup

; Hang if kernel exits.
.hang:
    cli
    hlt
    jmp .hang
.end:
