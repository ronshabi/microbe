global _start
global stack_bottom
global stack_top
extern kmain

MB_ALIGN        equ 1<<0
MB_MEMINFO      equ 1<<1
MB_FLAGS        equ MB_ALIGN | MB_MEMINFO
MB_MAGIC        equ 0x1BADB002
MB_CHECKSUM     equ -(MB_MAGIC + MB_FLAGS)

section .multiboot

align 4

dd MB_MAGIC
dd MB_FLAGS
dd MB_CHECKSUM

section .bss
align 16

stack_bottom:
resb 16384 ; Reserve 16KiB for stack
stack_top:

section .text
_start:
    mov esp, stack_top
    cli
    call kmain
    hlt

unreachable:
    jmp unreachable
    hlt