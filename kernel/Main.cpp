#include "kernel/GlobalDescriptorTable.h"
#include <kernel/VGA.h>
#include <kernel/Printk.h>
#include <kernel/ProtectedMode.h>
#include <kernel/Libk.h>

extern "C" void kmain();
extern "C" u32 g_GDTR;

VGA* g_VGA;

void kmain() {
  VGA driver{};
  g_VGA = &driver;

  // GlobalDescriptorTable gdt{};

  printk("Hello world\n");
  errprintk("Panic!!!\n");

}
