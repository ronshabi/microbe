#include <kernel/Types.h>
#include <stdarg.h>

void snprintk(char* buffer, const char* fmt, va_list v);
void printk(const char* fmt, ...);