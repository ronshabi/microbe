#include "vga.hpp"

#include <kernel/libk.hpp>

VGA::VGA() noexcept { memset(m_buffer, 0, m_width * m_height); }

void VGA::put_char(char c) {
  if (c == '\n') {
    advance_newline();
  } else {
    m_buffer[m_y * m_width + m_x] = (c | 0xf << 8);
    advance_cursor();
  }
}

void VGA::put_string(const char* s) {
  while (*s) {
    put_char(*s);
    s++;
  }
}

void VGA::advance_newline() {
  // FIXME: implement scrolling
  m_x = 0;
  m_y++;
}

void VGA::advance_cursor() {
  if (m_x != m_width - 1) {
    m_x++;
  } else {
    advance_newline();
  }
}