#include "Analog_Model.h"
#include "Analog_Hardware.h"
#include "Analog_Conductor.h"

void AnalogConductor_Init(void)
{
    AnalogHardware_Init();
    AnalogModel_Init();
}