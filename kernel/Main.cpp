#include <kernel/VGA.h>
#include <kernel/Printk.h>
#include <kernel/ProtectedMode.h>
#include <kernel/Libk.h>

extern "C" void kmain();
extern "C" u32 g_GDTR;

VGA* g_VGA;
TaskSegmentDescriptor t{};
extern u8 core_mempool;

void kmain() {
  VGA driver{};

  g_VGA = &driver;

  printk("Tss is @ 0x%x\n", &t);

  printk("The GDTR location is %x\n", &g_GDTR);

  FillGdt();
  // FIXME: fill in
  register_gdt(65535, core_mempool);
}
