#include <kernel/Libk.h>
#include <kernel/Printk.h>

#include <kernel/VGA.h>

#include <kernel/GlobalDescriptorTable.h>
#include <kernel/InterruptDescriptorTable.h>


extern "C" u32 g_GDTR;

VGA* g_VGA;

extern "C" void kmain() {
  GlobalDescriptorTable gdt{};
  InterruptDescriptorTable idt{};
  VGA driver{};
  g_VGA = &driver;


  printk("Hello world\n");
  errprintk("Panic!!!\n");
}