#include "Common.h"

void CPU::Out8(u16 port, u8 value)
{
    asm volatile("outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

u8 CPU::In8(u16 port)
{
    u8 ret = 0;
    asm volatile("outb %0, %1" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

void CPU::IOWait()
{
    Out8(0x80, 0);
}

bool CPU::AreInterruptsEnabled()
{
    u32 flags;
    asm volatile ("pushf\n\t"
                  "pop %0"
                   : "=g"(flags));

    return flags & (1 << 9);
}