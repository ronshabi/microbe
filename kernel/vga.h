#pragma once

#include <kernel/types.h>

class VGA {
public:
  explicit VGA() noexcept;
  void put_char(char c);
  void put_string(const char* s);
private:
  void advance_cursor();
  void advance_newline();

private:
  const u32 m_width{80};
  const u32 m_height{25};
  u32 m_x{0};
  u32 m_y{0};
  u16* m_buffer{reinterpret_cast<u16*>(0xB8000)};
};