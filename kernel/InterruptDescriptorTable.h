#pragma once

#include <kernel/InterruptDescriptorTableEntry.h>
#include <kernel/Types.h>
#include <kernel/Libk.h>

extern "C" void RegisterIDT(u32 size, u32 offset); 

class InterruptDescriptorTable {
public:
    InterruptDescriptorTable();
private:
    static constexpr auto IDT_TABLE_SIZE = 256;

    __attribute__((aligned(0x10))) InterruptDescriptorTableEntry m_table[IDT_TABLE_SIZE];
} __attribute__((packed));