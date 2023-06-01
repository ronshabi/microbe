#pragma once

#include <kernel/InterruptDescriptorTableEntry.h>
#include <kernel/Types.h>
#include <kernel/Libk.h>
#include <kernel/Printk.h>

extern "C" void RegisterIDT(u32 size, u32 offset);
extern "C" u32* isr_stub_table[];

// FIXME: move
extern "C" void ExceptionHandler(void);



class InterruptDescriptorTable {
public:
    InterruptDescriptorTable();
private:
    static constexpr auto IDT_TABLE_SIZE = 256;
    void SetDescriptor(u32 index, u32* isr, u8 flags);

    __attribute__((aligned(0x10))) InterruptDescriptorTableEntry m_table[IDT_TABLE_SIZE];
} __attribute__((packed));