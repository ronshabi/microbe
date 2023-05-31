#include "SegmentDescriptor.h"

SegmentDescriptor::SegmentDescriptor()
{
    // Do nothing, this is a null descriptor constructor
}

SegmentDescriptor::SegmentDescriptor(u32 base, u32 limit, u8 flags, u8 access_byte)
    : m_limit_0(limit & 0xFFFF)
    , m_base_0(base & 0xFFFF)
    , m_base_1((base >> 16) & 0xFFFF)
    , m_access_byte(access_byte)
    , m_flags(static_cast<u8>((limit >> 16) & 0xF) | static_cast<u8>((static_cast<u16>(flags) << 4) & 0xF0))
    , m_base_2((base >> 24) & 0xFF)
{
    // FIXME: are the flags correct?
}