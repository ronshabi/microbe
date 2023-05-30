#include <kernel/vga.hpp>

static_assert(sizeof(int) == 4, "int => 4");
static_assert(sizeof(long) == 4, "int => 4");

extern "C" void kmain();

VGA* v;

void kmain() {
  VGA driver;
  v = &driver;

  v->put_string("Hello guys\n");
  v->put_string("Hows it going bros\n");
}