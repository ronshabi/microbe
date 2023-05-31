#include "GlobalDescriptorTable.h"

GlobalDescriptorTable::GlobalDescriptorTable()
{
    u16 size = lgdt_size;
    u32 location = reinterpret_cast<u32>(GetGDTAddress());
    printk("GDT LOCATION = %x\n", location);

    // u64 gdtr = 0;
    // gdtr |= size;
    // gdtr |= (static_cast<u64>(location) << 16);

    // asm("lgdt %0\n": : "m"(gdtr));

    register_gdt(lgdt_size, location);
}

SegmentDescriptor* GlobalDescriptorTable::GetGDTAddress()
{
    return &this->m_null;
}