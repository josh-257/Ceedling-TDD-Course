#ifndef DIGITAL_H
#define DIGITAL_H

#include <stdint.h>
#include "Utils.h"
#include "LPC1768.h"


void Digital_Init(void);
uint8_t Digital_GetBits(void);

#endif // DIGITAL_H