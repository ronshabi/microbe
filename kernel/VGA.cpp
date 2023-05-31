#include <kernel/Libk.h>
#include <kernel/VGA.h>

VGA::VGA() noexcept { memset(m_buffer, 0, m_width * m_height); }

void VGA::PutChar(char c)
{
    if (c == '\n') {
        AdvanceNewline();
    } else {
        m_buffer[m_y * m_width + m_x] = CharWithColor(c, m_color);
        AdvanceCursor();
    }
}

void VGA::PutString(const char* s)
{
    while (*s) {
        PutChar(*s);
        s++;
    }
}

void VGA::AdvanceNewline()
{
    // FIXME: implement scrolling
    m_x = 0;
    m_y++;
}

void VGA::AdvanceCursor()
{
    if (m_x != m_width - 1) {
        m_x++;
    } else {
        AdvanceNewline();
    }
}

u8 VGA::Color(u8 fg, u8 bg) {
    return fg | (bg << 4);
}

u16 VGA::CharWithColor(u8 c, u8 color) {
    return (static_cast<u16>(c) | (static_cast<u16>(color) << 8));
}

void VGA::SetColor(u8 fg, u8 bg) {
    m_color = VGA::Color(fg, bg);
}