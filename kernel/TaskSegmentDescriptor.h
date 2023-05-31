#pragma once

#include <kernel/Types.h>

struct TaskSegmentDescriptor {
    u16 LINK{0};
    u16 LINK_RESERVED{0};
    u32 ESP0{0};
    u16 SS0{0};
    u16 SS0_RESERVED{0};
    u32 ESP1{0};
    u16 SS1{0};
    u16 SS1_RESERVED{0};
    u32 ESP2{0};
    u16 SS2{0};
    u16 SS2_RESERVED{0};
    u32 CR3{0};
    u32 EIP{0};
    u32 EFLAGS{0};
    u32 EAX{0};
    u32 ECX{0};
    u32 EDX{0};
    u32 EBX{0};
    u32 ESP{0};
    u32 EBP{0};
    u32 ESI{0};
    u32 EDI{0};
    u16 ES{0};
    u16 ES_RESERVED{0};
    u16 CS{0};
    u16 CS_RESERVED{0};
    u16 SS{0};
    u16 SS_RESERVED{0};
    u16 DS{0};
    u16 DS_RESERVED{0};
    u16 FS{0};
    u16 FS_RESERVED{0};
    u16 GS{0};
    u16 GS_RESERVED{0};
    u16 LDTR{0};
    u16 LDTR_RESERVED{0};
    u16 IBOP_RESERVED{0};
    u16 IOBP{0};
    u32 SSP{0};

public:
    TaskSegmentDescriptor(u16 ss0, u32 esp0, u16 iobp);
} __attribute__((packed));

static_assert(sizeof(TaskSegmentDescriptor) == 108, "TSS size should be 108 bytes.");