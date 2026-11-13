#include "Analog_Model.h"

static uint16_t AnalogValues[NUM_ADC_CHANNELS];

void AnalogModel_Init(void)
{
    for(int i = 0; i < NUM_ADC_CHANNELS; i++)
    {
        AnalogValues[i] = 0;
    }
}

uint16_t AnalogModel_GetChannel(AdcChanel_t channel)
{
    if(channel < NUM_ADC_CHANNELS)
    {
        return AnalogValues[channel];
    }
    else
    {
        return 0;
    }
}