#include "Filter.h"
#include <stdint.h>

uint16_t Filter_AddVal(uint16_t PrevVal, uint16_t NewVal)
{
    return (uint16_t)((3 * (uint32_t)PrevVal + (uint32_t)NewVal + 2) / 4);
}
