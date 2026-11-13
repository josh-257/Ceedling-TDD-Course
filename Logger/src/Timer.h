#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void Timer_Init(void);
void Timer_WaitMilli(uint32_t msec);

#endif // TIMER_H
