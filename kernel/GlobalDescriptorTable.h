#pragma once

#include <kernel/SegmentDescriptor.h>
#include <kernel/TaskSegmentDescriptor.h>
#include <kernel/Types.h>
#include <kernel/Printk.h>

extern "C" void RegisterGDT(u32 size, u32 offset);

class GlobalDescriptorTable {
public:
    GlobalDescriptorTable();

    SegmentDescriptor* GetGDTAddress();
private:
    constexpr static u32 lgdt_size = 6 * 8 - 1;

    TaskSegmentDescriptor m_tss_object { 0x10, 0x0, 104 };
    SegmentDescriptor m_null {};
    SegmentDescriptor m_sg_k_code { 0, 0xFFFFF, 0x9A, 0x0C };
    SegmentDescriptor m_sg_k_data { 0, 0xFFFFF, 0x92, 0x0C };
    SegmentDescriptor m_sg_u_code { 0, 0xFFFFF, 0xFA, 0x0C };
    SegmentDescriptor m_sg_u_data { 0, 0xFFFFF, 0xF2, 0x0C };

    SegmentDescriptor m_sg_tss { reinterpret_cast<u32>(&m_tss_object),
        sizeof(TaskSegmentDescriptor), 0x89, 0 };
} __attribute__((packed));
