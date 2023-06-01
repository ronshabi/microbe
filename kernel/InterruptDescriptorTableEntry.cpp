#include "InterruptDescriptorTableEntry.h"

InterruptDescriptorTableEntry::InterruptDescriptorTableEntry()
{

}

void InterruptDescriptorTableEntry::SetISR(u32* ptr) {
    u32 ptr_as_u32 = reinterpret_cast<u32>(ptr);
    m_isr_low = (ptr_as_u32 & 0xFFFF);
    m_isr_high = ((ptr_as_u32 >> 16) & 0xFFFF);
}

void InterruptDescriptorTableEntry::SetFlags(u8 flags) {
    m_attributes = flags;
}

void InterruptDescriptorTableEntry::SetKernelCS(u16 kernelcs)
{
    m_kernel_cs = kernelcs;    
}
