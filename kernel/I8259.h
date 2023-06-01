#pragma once

#include <kernel/Common.h>
#include <kernel/Types.h>

class PIC 
{
public:
    PIC(u8 command_port, u8 data_port, u8 remap_to);

    u8 GetState();
    void SendCommand(u8 command);
    void SendData(u8 data);
    void Remap();

    static constexpr u8 EndOfInterrupt { 0x20 };
    static constexpr u8 Initialize { 0x11 };
    static constexpr u8 Use8086Mode { 0x01 };
private:
    const u8 m_command_port;
    const u8 m_data_port;
    const u8 m_remap_to;
};

class I8259 {
public:
    I8259();
    void SendEOI(u8 irq);
private:
    PIC m_PIC1;
    PIC m_PIC2;
};