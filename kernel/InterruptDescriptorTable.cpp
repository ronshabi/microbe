#include "InterruptDescriptorTable.h"
#include "kernel/InterruptDescriptorTableEntry.h"

InterruptDescriptorTable::InterruptDescriptorTable()
{
    memset(m_table, 0, IDT_TABLE_SIZE);
    
    for (int vector = 0; vector < 32; vector++) {
        SetDescriptor(vector, isr_stub_table[vector], 0x8E);
    }

    // Register IDT
    constexpr u32 size = IDT_TABLE_SIZE * sizeof(InterruptDescriptorTableEntry) - 1;
    RegisterIDT(size, reinterpret_cast<u32>(m_table));
}

void InterruptDescriptorTable::SetDescriptor(u32 index, void* isr, u8 flags)
{
    m_table[index].SetFlags(flags);
    m_table[index].SetISR(isr);
    m_table[index].SetKernelCS(0x08);
}


void ExceptionHandler()
{
    errprintk("Exception Handler called\n");
    asm volatile ("cli; hlt");
}

