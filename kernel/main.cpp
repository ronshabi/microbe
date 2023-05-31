#include <kernel/vga.hpp>
#include <kernel/printk.hpp>

extern "C" void kmain();

VGA* g_VGA;

void kmain() {
  VGA driver{};
  g_VGA = &driver;

  printk("Hello guys %x\n", 0x42069);
  printk("Hows it going bros\n");
}