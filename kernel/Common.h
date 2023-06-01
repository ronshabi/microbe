#include <kernel/Types.h>

// CPU IO
namespace CPU {
void Out8(u16 port, u8 value);
u8 In8(u16 port);
void IOWait();
bool AreInterruptsEnabled();
}
