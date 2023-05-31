#pragma once

#include <kernel/Types.h>

class VGA {
public:
  explicit VGA() noexcept;
  void PutChar(char c);
  void PutString(const char* s);
private:
  void AdvanceCursor();
  void AdvanceNewline();

private:
  const u32 m_width{80};
  const u32 m_height{25};
  u32 m_x{0};
  u32 m_y{0};
  u16* m_buffer{reinterpret_cast<u16*>(0xB8000)};
};