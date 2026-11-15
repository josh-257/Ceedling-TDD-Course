#include "Executor.h"
#include "LED.h"
#include "Digital.h"
#include "Analog_Conductor.h"
#include "Analog_Model.h"
#include <stdint.h>

void Executor_Init(void)
{
    LED_Init();
    Digital_Init();
    AnalogConductor_Init();
}

bool Executor_Exec(void)
{
    //Iteration 2
    if(AnalogModel_GetChannel(ADC0) > AnalogModel_GetChannel(ADC1))
    {
        LED_On(LED1);
    }
    else
    {
        LED_Off(LED1);
    }

    if(AnalogModel_GetChannel(ADC2) > AnalogModel_GetChannel(ADC3))
    {
        LED_On(LED2);
    }
    else
    {
        LED_Off(LED2);
    }

    if(AnalogModel_GetChannel(ADC4) > AnalogModel_GetChannel(ADC5))
    {
        LED_On(LED3);
    }
    else
    {
        LED_Off(LED3);
    }

    LED_On(LED0);

    return true;
}