#include "Executor.h"
#include "Digital.h"
#include "LED.h"
#include "Analog.h"
#include <stdint.h>

void Executor_Init(void)
{
    LED_Init();
    Digital_Init();
}

bool Executor_Exec(void)
{
    uint8_t bits = Digital_GetBits();
      
    if((bits & 0x3) == 0)
    {
        LED_Off(LED0);
    }
    else
    {
        LED_Toggle(LED0);
    }

    if((bits & (0x3 << 2)) == 0)
    {
        LED_Off(LED1);
    }
    else
    {
        LED_Toggle(LED1);
    }

    if((bits & (0x3 << 4)) == 0)
    {
        LED_Off(LED2);
    }
    else
    {
        LED_Toggle(LED2);
    }

    if(Analog_ReadingReady())
    {
        if(Analog_GetReading(ADC0) > Analog_GetReading(ADC1))
        {
            LED_On(LED1);
        }
        else
        {
            LED_Off(LED1);
        }

        if(Analog_GetReading(ADC2) > Analog_GetReading(ADC3))
        {
            LED_On(LED2);
        }
        else
        {
            LED_Off(LED2);
        }

        if(Analog_GetReading(ADC4) > Analog_GetReading(ADC5))
        {
            LED_On(LED3);
        }
        else
        {
            LED_Off(LED3);
        }

        LED_On(LED0);
    }

   

    return true;
}