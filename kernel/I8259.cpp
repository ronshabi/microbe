#include "I8259.h"

PIC::PIC(u8 command_port, u8 data_port, u8 remap_to)
    : m_command_port(command_port)
    , m_data_port(data_port)
    , m_remap_to(remap_to)
{

}

u8 PIC::GetState()
{
    return CPU::In8(m_command_port);
}

void PIC::SendCommand(u8 command)
{
    CPU::Out8(m_command_port, command);
}


void PIC::SendData(u8 data)
{
    CPU::Out8(m_data_port, data);
}

void PIC::Remap() {
    SendData(m_remap_to);
}

// === I8259 =====================



I8259::I8259()
    : m_PIC1(0x20, 0x21, 0x20)
    , m_PIC2(0xA0, 0xA1, 0X28)
{
    // Save PICs state
    const auto pic1_state = m_PIC1.GetState();
    const auto pic2_state = m_PIC2.GetState();

    // Send init command
    m_PIC1.SendCommand(PIC::Initialize);
    CPU::IOWait();
    m_PIC2.SendCommand(PIC::Initialize);
    CPU::IOWait();

    // Data for init command
    // 1) Remap vector offsets
    
    m_PIC1.Remap();
    CPU::IOWait();
    m_PIC2.Remap();
    CPU::IOWait();

    // 2) Tell PIC1 that PIC2 is @ 4, tell PIC2 it's cascade identity @ 2
    m_PIC1.SendData(4);
    CPU::IOWait();
    m_PIC2.SendData(2);
    CPU::IOWait();

    // 2) Use 8086 mode instead of 8080 mode
    m_PIC1.SendData(PIC::Use8086Mode);
    CPU::IOWait();
    m_PIC2.SendData(PIC::Use8086Mode);
    CPU::IOWait();

    // Restore state
    m_PIC1.SendData(pic1_state);
    m_PIC1.SendData(pic2_state);
}


void I8259::SendEOI(u8 irq)
{
    if (irq >= 8) {
        m_PIC2.SendCommand(PIC::EndOfInterrupt);
    }

    m_PIC1.SendCommand(PIC::EndOfInterrupt);
}
