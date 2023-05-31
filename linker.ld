ENTRY(_start)

SECTIONS
{
    . = 1M;

    /* Put the multiboot header */
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.init)
        *(.text)
        *(.fini)
    }

    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}