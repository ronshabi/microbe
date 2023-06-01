#pragma once

#include <kernel/Common.h>
#include <kernel/Types.h>

namespace I8259 {
namespace PIC1 {
    constexpr u8 Command{0x20};
    constexpr u8 Data{Command + 1};
    constexpr u8 RemappedOffset{0x20};
}
namespace PIC2 {
    constexpr u8 Command{0xA0};
    constexpr u8 Data{Command + 1};
    constexpr u8 RemappedOffset{0x28};
}

namespace Commands {
    constexpr u8 EndOfInterrupt { 0x20 };
    constexpr u8 Initialize { 0x11 };
    constexpr u8 Use8086Mode { 0x01 };
}

void SendEOI(u8 irq);
void Init();
}