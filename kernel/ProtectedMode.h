#pragma once

#include <kernel/Types.h>

extern "C" void register_gdt(u32 size, u32 offset);

struct TaskSegmentDescriptor {
    u16 link;
    u16 link_RESERVED;
    u32 esp0;
    u16 ss0;
    u16 ss0_RESERVED;
    u32 esp1;
    u16 ss1;
    u16 ss1_RESERVED;
    u32 esp2;
    u16 ss2;
    u16 ss2_RESERVED;
    u32 cr3;
    u32 eip;
    u32 eflags;
    u32 eax;
    u32 ecx;
    u32 edx;
    u32 ebx;
    u32 esp;
    u32 ebp;
    u32 esi;
    u32 edi;
    u16 es;
    u16 es_RESERVED;
    u16 cs;
    u16 cs_RESERVED;
    u16 ss;
    u16 ss_RESERVED;
    u16 ds;
    u16 ds_RESERVED;
    u16 fs;
    u16 fs_RESERVED;
    u16 gs;
    u16 gs_RESERVED;
    u16 ldtr;
    u16 ldtr_RESERVED;
    u16 ibop_RESERVED;
    u16 iobp;
    u32 ssp;
} __attribute__((packed));

static_assert(sizeof(TaskSegmentDescriptor) == 108, "TSS size should be 108 bytes.");

void FillGdt();
void EncodeGdtEntry(u8* mempool, u32 descriptor_index, u32 base, u32 limit, u32 flags, u32 access_byte);