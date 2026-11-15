

#include "unity.h"
#include "MockLED.h"
#include "MockDigital.h"
#include "MockAnalog_Conductor.h"
#include "MockAnalog_Model.h"
#include "Executor.h"

void setUp(void)
{
}

void tearDown(void)
{
}

static void AllExpectLedOff(void)
{
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);
}

static void expectReadings(uint16_t a0, uint16_t a1, uint16_t a2,
                           uint16_t a3, uint16_t a4, uint16_t a5)
{
    AnalogModel_GetChannel_ExpectAndReturn(ADC0, a0);
    AnalogModel_GetChannel_ExpectAndReturn(ADC1, a1);
    AnalogModel_GetChannel_ExpectAndReturn(ADC2, a2);
    AnalogModel_GetChannel_ExpectAndReturn(ADC3, a3);
    AnalogModel_GetChannel_ExpectAndReturn(ADC4, a4);
    AnalogModel_GetChannel_ExpectAndReturn(ADC5, a5);
}

void test_Executor_Init_should_InitializeAllSubsystems(void)
{
    LED_Init_Expect();
    Digital_Init_Expect();
    AnalogConductor_Init_Expect();
    Executor_Init();
}

void test_Executor_Exec_should_ToggleLED1IfAdc0HigherthanAdc1(void)
{
    AnalogConductor_Exec_Expect();
    expectReadings(5, 3, 0, 0, 0, 0);
    LED_On_Expect(LED1);
    LED_Off_Expect(LED2);
    LED_Off_Expect(LED3);
    LED_On_Expect(LED0);
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLED1IfAdc2HigherthanAdc3(void)
{
    AnalogConductor_Exec_Expect();
    LED_On_Expect(LED2);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED3);
    expectReadings(0, 0, 3, 2, 0, 0);
    LED_On_Expect(LED0);
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLED1IfAdc4HigherthanAdc5(void)
{
    AnalogConductor_Exec_Expect();
    LED_On_Expect(LED3);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);
    expectReadings(0, 0, 0, 0, 10, 9);
    LED_On_Expect(LED0);
    Executor_Exec();
}