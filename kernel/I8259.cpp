#include "I8259.h"

void I8259::SendEOI(u8 irq)
{
    if (irq >= 8) {
        CPU::Out8(PIC2::Command, Commands::EndOfInterrupt);
    }

    CPU::Out8(PIC1::Command, Commands::EndOfInterrupt);
}

void I8259::Init()
{
    // Save PIC state
    const auto pic1_state = CPU::In8(PIC1::Command);
    const auto pic2_state = CPU::In8(PIC2::Command);

    // Send init command
    CPU::Out8(PIC1::Command, Commands::Initialize);
    CPU::IOWait();
    CPU::Out8(PIC2::Command, Commands::Initialize);
    CPU::IOWait();

    // Data for init command
    // 1) Remap vector offsets
    CPU::Out8(PIC1::Data, PIC1::RemappedOffset);
    CPU::IOWait();
    CPU::Out8(PIC2::Data, PIC2::RemappedOffset);
    CPU::IOWait();

    // 2) Tell PIC1 that PIC2 is @ 4, tell PIC2 it's cascade identity @ 2
    CPU::Out8(PIC1::Data, 4);
    CPU::IOWait();
    CPU::Out8(PIC2::Data, 2);
    CPU::IOWait();

    // 2) Use 8086 mode instead of 8080 mode
    CPU::Out8(PIC1::Data, Commands::Use8086Mode);
    CPU::IOWait();
    CPU::Out8(PIC2::Data, Commands::Use8086Mode);
    CPU::IOWait();

    // Restore state
    CPU::Out8(PIC1::Data, pic1_state);
    CPU::Out8(PIC2::Data, pic2_state);

}
