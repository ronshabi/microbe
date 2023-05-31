#pragma once

#include <kernel/Types.h>

class SegmentDescriptor {
public:
    SegmentDescriptor();
    SegmentDescriptor(u32 base, u32 limit, u8 flags, u8 access_byte);

private:
    u16 m_limit_0 { 0 };
    u16 m_base_0 { 0 };
    u8 m_base_1 { 0 };
    u8 m_access_byte { 0 };
    u8 m_flags { 0 };
    u8 m_base_2 { 0 };
} __attribute__((packed));

static_assert(sizeof(SegmentDescriptor) == 8,
    "Size of a segment descriptor class should be 8 bytes");