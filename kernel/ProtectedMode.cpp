#include <kernel/Libk.h>
#include <kernel/Printk.h>
#include <kernel/ProtectedMode.h>

constexpr int core_mempool_size = 1024;
u8 core_mempool[core_mempool_size];

extern TaskSegmentDescriptor t;

void FillGdt() {
  memset(core_mempool, 0, core_mempool_size);

  // Null descriptor
  EncodeGdtEntry(core_mempool, 0, 0, 0, 0, 0);
  EncodeGdtEntry(core_mempool, 1, 0, 0xFFFFF, 0x9A, 0x0C);
  EncodeGdtEntry(core_mempool, 2, 0, 0xFFFFF, 0x92, 0x0C);
  EncodeGdtEntry(core_mempool, 3, 0, 0xFFFFF, 0xFA, 0x0C);
  EncodeGdtEntry(core_mempool, 4, 0, 0xFFFFF, 0xF2, 0x0C);

  // TSS
  memset(&t, 0, sizeof(TaskSegmentDescriptor));
  t.ss0 = 0x10;
  t.esp0 = 0x0; // Stack pointer when we get a syscall
  t.iobp = 104;
}

void EncodeGdtEntry(u8* mempool, u32 descriptor_index, u32 base, u32 limit,
                    u32 flags, u32 access_byte) {
  // Check the limit to make sure that it can be encoded
  if (limit > 0xFFFFF) {
    printk("GDT cannot encode limits larger than 0xFFFFF");
  }

  descriptor_index *= 8; // each descriptor is 8 bytes

  printk("Assigning descriptor at offset 0x%x\n", descriptor_index);

  // Encode the limit
  mempool[descriptor_index + 0] |= limit & 0xFF;
  mempool[descriptor_index + 1] |= (limit >> 8) & 0xFF;
  mempool[descriptor_index + 6] |= (limit >> 16) & 0x0F;

  // Encode the base
  mempool[descriptor_index + 2] |= base & 0xFF;
  mempool[descriptor_index + 3] |= (base >> 8) & 0xFF;
  mempool[descriptor_index + 4] |= (base >> 16) & 0xFF;
  mempool[descriptor_index + 7] |= (base >> 24) & 0xFF;

  // Encode the access byte
  mempool[descriptor_index + 5] |= access_byte;

  // Encode the flags
  mempool[descriptor_index + 6] |= (flags << 4);
}