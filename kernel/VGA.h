#pragma once

#include <kernel/Types.h>

class VGA {
public:
    explicit VGA() noexcept;
    void PutChar(char c);
    void PutString(const char* s);
    void SetColor(u8 fg, u8 bg);

    enum Colors {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        LightBrown = 14,
        White = 15,
    };

private:
    static u16 CharWithColor(u8 c, u8 color);
    static u8 Color(u8 fg, u8 bg);

    void AdvanceCursor();
    void AdvanceNewline();
private:
    const u32 m_width { 80 };
    const u32 m_height { 25 };
    u32 m_x { 0 };
    u32 m_y { 0 };
    u8 m_color{Color(White, Black)};
    u16* m_buffer { reinterpret_cast<u16*>(0xB8000) };
};