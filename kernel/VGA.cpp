#include <kernel/Libk.h>
#include <kernel/VGA.h>

VGA::VGA() noexcept { memset(m_buffer, 0, m_width * m_height); }

void VGA::PutChar(char c) {
  if (c == '\n') {
    AdvanceNewline();
  } else {
    m_buffer[m_y * m_width + m_x] = (c | 0xf << 8);
    AdvanceCursor();
  }
}

void VGA::PutString(const char* s) {
  while (*s) {
    PutChar(*s);
    s++;
  }
}

void VGA::AdvanceNewline() {
  // FIXME: implement scrolling
  m_x = 0;
  m_y++;
}

void VGA::AdvanceCursor() {
  if (m_x != m_width - 1) {
    m_x++;
  } else {
    AdvanceNewline();
  }
}