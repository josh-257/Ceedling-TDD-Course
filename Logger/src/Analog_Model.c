#include "Analog_Model.h"
#include "Filter.h"

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

void AnalogModel_AddReading(AdcChanel_t channel, uint16_t reading)
{
    if(channel < NUM_ADC_CHANNELS)
    {
        AnalogValues[channel] = Filter_AddVal(AnalogValues[channel], reading);
    }
}