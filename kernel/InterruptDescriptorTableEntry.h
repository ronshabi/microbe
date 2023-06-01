#pragma once

#include <kernel/Types.h>

class InterruptDescriptorTableEntry
{
public:
    InterruptDescriptorTableEntry();
private:
    u16 m_isr_low{0};
    u16 m_kernel_cs{0};
    u8 m_reserved{0};
    u8 m_attributes{0};
    u16 m_isr_high{0};
} __attribute__((packed));

static_assert(sizeof(InterruptDescriptorTableEntry) == 8, "IDT Entry should be 8 bytes long");