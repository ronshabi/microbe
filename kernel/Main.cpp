#include <kernel/Libk.h>
#include <kernel/Printk.h>
#include <kernel/Common.h>
#include <kernel/I8259.h>

#include <kernel/VGA.h>

#include <kernel/GlobalDescriptorTable.h>
#include <kernel/InterruptDescriptorTable.h>


extern "C" u32 g_GDTR;

VGA* g_VGA;

extern "C" void kmain() {
  GlobalDescriptorTable gdt{};
  InterruptDescriptorTable idt{};
  I8259 i8259{};
  i8259.UnsetMask(0);


  VGA driver{};
  g_VGA = &driver;


  printk("Are Interrupts enabled? %d\n", CPU::AreInterruptsEnabled());
  errprintk("Panic!!!\n");

}