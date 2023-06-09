global _start
global stack_bottom
global stack_top
extern kmain
extern _init

extern ExceptionHandler

global g_GDTR
global g_IDTR

global RegisterGDT
global RegisterTSS
global isr_stub_table
global RegisterIDT

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

; === TEXT ========================

section .text
_start:
    mov esp, stack_top
    call kmain
    cli
    hlt

unreachable:
    jmp unreachable
    hlt

RegisterGDT:
    ; Load data from C++ function into the GDT register
    xor eax, eax
    mov ax, [esp + 4]            ; get size (16 bits) - which is the first parameter in C++ func
    mov [g_GDTR], ax                ; load size into GDTR data structure
    
    mov eax, [esp + 8]          ; get offset (32 bits) - which is the last parameter in C++ func
    mov [g_GDTR + 2], eax           ; load offset into GDTR

    ; Disable Interrutps
    cli
    
    ; Load the GDT register into the CPU
    mov eax, g_GDTR
    lgdt [eax]
    ret

ReloadSegments:
    jmp 0x08:.reload_cs

.reload_cs:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

RegisterTSS:
    xor eax, eax    ; zero out EAX for safety
    mov ax, 0x28    ; the TSS is the 6th element in the GDT => index is 5 => 5*8=0x28
    ltr ax          ; load task register for TSS
    ret

;
; IDT
;
RegisterIDT:
    xor eax, eax
    mov ax, [esp + 4]       ; First paramter - size as u32 in C++ to 16 bit in asm
    mov [g_IDTR], ax        ; Load size into data structure
    
    mov eax, [esp + 8]      ; Second paramter - offset as u32
    mov [g_IDTR+2], eax     ; Load Offset into data structure

    mov eax, g_IDTR         ; Load the data structure locaiton to EAX 
    lidt [eax]              ; Register IDT
    sti                     ; Enable interrupts
    ret


; ------------------------------------------------
; Data Section
; ------------------------------------------------
section .data
g_GDTR:
    dw 0    ; size
    dd 0    ; offset

g_IDTR:
    dw 0    ; size
    dd 0    ; offset





; === INTERRUPTS ================================================================

%macro isr_err_stub 1
isr_stub_%+%1:
    call ExceptionHandler
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    call ExceptionHandler
    iret
%endmacro

isr_no_err_stub 0
isr_no_err_stub 1
isr_no_err_stub 2
isr_no_err_stub 3
isr_no_err_stub 4
isr_no_err_stub 5
isr_no_err_stub 6
isr_no_err_stub 7
isr_err_stub    8
isr_no_err_stub 9
isr_err_stub    10
isr_err_stub    11
isr_err_stub    12
isr_err_stub    13
isr_err_stub    14
isr_no_err_stub 15
isr_no_err_stub 16
isr_err_stub    17
isr_no_err_stub 18
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_err_stub    30
isr_no_err_stub 31

isr_stub_table:
%assign i 0
%rep    32
    dd isr_stub_%+i
%assign i i+1
%endrep
