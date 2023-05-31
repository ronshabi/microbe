#include "TaskSegmentDescriptor.h"

TaskSegmentDescriptor::TaskSegmentDescriptor(u16 ss0, u32 esp0, u16 iobp)
    : ESP0(esp0)
    , SS0(ss0)
    , IOBP(iobp)
{
}