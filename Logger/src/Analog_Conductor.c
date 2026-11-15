#include "Analog_Model.h"
#include "Analog_Hardware.h"
#include "Analog_Conductor.h"

void AnalogConductor_Init(void)
{
    AnalogHardware_Init();
    AnalogModel_Init();
}

void AnalogConductor_Exec(void)
{
    uint16_t Value;
    for(uint8_t i = 0; i < NUM_ADC_CHANNELS; i++)
    {
        if(AnalogHardware_IsReady(i) == STATUS_OK)
        {
            Value = AnalogHardware_GetReading(i);
            AnalogModel_AddReading(i, Value);
        }
    }
}