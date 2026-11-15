#include "Timer.h"
#include "Core.h"
#include <stdint.h>

#ifdef TEST
uint32_t TestCounter;
#define WAIT_UNTIL_EQUAL(a,b) while(a++ != b)  { TestCounter++; }
#else
#define WAIT_UNTIL_EQUAL(a,b) while(a != b) {}
#endif

static uint32_t TimeStamp;

void Timer_Init(void)
{
    //Create tick rate
    uint32_t counts_per_tick = __CORE_CLK / 100;

    //Disable so we can config
    SysTick->CTRL = ~SysTick_CTRL_CLKSOURCE_Msk;
    //Assign our Tick Rate
    SysTick->LOAD = counts_per_tick - 1;
    //Set starting timer value to 0
    SysTick->VAL = 0UL;
    //Enable timer source, using tick interrupt 
    //and start timer
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |
                    SysTick_CTRL_TICKINT_Msk   |
                    SysTick_CTRL_ENABLE_Msk;

    TimeStamp = 0;
}

void Timer_WaitMilli(uint32_t msec)
{
    uint32_t Goal = TimeStamp + msec;
    WAIT_UNTIL_EQUAL(TimeStamp, Goal);
}

void Timer_SetStamp(uint32_t Stamp)
{
    TimeStamp = Stamp;
}

uint32_t Timer_GetStamp(void)
{
    return TimeStamp;
}

uint32_t Timer_WaitRemainder(uint32_t StartStamp, uint32_t msec)
{
    uint32_t Goal = StartStamp + msec;
    WAIT_UNTIL_EQUAL(TimeStamp, Goal);
    return TimeStamp;
}

void SysTick_Handler(void)
{
    TimeStamp += 10;
}