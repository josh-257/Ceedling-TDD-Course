#include "Timer.h"
#include "Core.h"

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

}