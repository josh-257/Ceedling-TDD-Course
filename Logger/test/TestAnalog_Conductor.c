#include "unity.h"
#include "MockAnalog_Model.h"
#include "MockAnalog_Hardware.h"
#include "Analog_Conductor.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Analog_Conductor_Init_should_InitSubmodules(void)
{
    AnalogModel_Init_Expect();
    AnalogHardware_Init_Expect();

    AnalogConductor_Init();
}
