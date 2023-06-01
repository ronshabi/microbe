#include "InterruptDescriptorTable.h"
#include "kernel/InterruptDescriptorTableEntry.h"

InterruptDescriptorTable::InterruptDescriptorTable()
{
    memset(m_table, 0, IDT_TABLE_SIZE);

    constexpr u32 size = IDT_TABLE_SIZE * sizeof(InterruptDescriptorTableEntry) - 1;

    RegisterIDT(size, reinterpret_cast<u32>(m_table));
}