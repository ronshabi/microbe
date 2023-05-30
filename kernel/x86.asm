global register_gdt
global register_tss
global isr_stub_table

; FIXME: move the inline asm to a funciton in here
global register_idt

k_code_segment_descriptor_offset EQU 0x08
k_data_segment_descriptor_offset EQU 0x10

register_gdt:
    cli
    mov eax, [esp+4] ; gdtr as parameter passed on the stack
    lgdt [eax]

    ; Reload segments
    ; Reload CS by performing a far jump
    jmp k_code_segment_descriptor_offset:.reload_cs

.reload_cs:
    mov ax, k_data_segment_descriptor_offset
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret

register_tss:
    mov ax, 0x28 ; the TSS is the 6th element in the GDT => index is 5 => 5*8=0x28
    ltr ax ; load task register for TSS
    ret

register_idt:
    mov eax, [esp+4] ; idtr as parameter passed on the stack
    lidt [eax]
    ret


; === INTERRUPTS ================================================================

; %macro isr_err_stub 1
; isr_stub_%+%1:
;     call exception_handler
;     iret
; %endmacro

; %macro isr_no_err_stub 1
; isr_stub_%+%1:
;     call exception_handler
;     iret
; %endmacro

; extern exception_handler
; isr_no_err_stub 0
; isr_no_err_stub 1
; isr_no_err_stub 2
; isr_no_err_stub 3
; isr_no_err_stub 4
; isr_no_err_stub 5
; isr_no_err_stub 6
; isr_no_err_stub 7
; isr_err_stub    8
; isr_no_err_stub 9
; isr_err_stub    10
; isr_err_stub    11
; isr_err_stub    12
; isr_err_stub    13
; isr_err_stub    14
; isr_no_err_stub 15
; isr_no_err_stub 16
; isr_err_stub    17
; isr_no_err_stub 18
; isr_no_err_stub 19
; isr_no_err_stub 20
; isr_no_err_stub 21
; isr_no_err_stub 22
; isr_no_err_stub 23
; isr_no_err_stub 24
; isr_no_err_stub 25
; isr_no_err_stub 26
; isr_no_err_stub 27
; isr_no_err_stub 28
; isr_no_err_stub 29
; isr_err_stub    30
; isr_no_err_stub 31

; isr_stub_table:
; %assign i 0
; %rep    32
;     dd isr_stub_%+i ; use DQ instead if targeting 64-bit
; %assign i i+1
; %endrep
