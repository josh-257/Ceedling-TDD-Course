

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
    Analog_GetReading_ExpectAndReturn(ADC0, a0);
    Analog_GetReading_ExpectAndReturn(ADC1, a1);
    Analog_GetReading_ExpectAndReturn(ADC2, a2);
    Analog_GetReading_ExpectAndReturn(ADC3, a3);
    Analog_GetReading_ExpectAndReturn(ADC4, a4);
    Analog_GetReading_ExpectAndReturn(ADC5, a5);
}

void test_Executor_Init_should_InitializeAllSubsystems(void)
{
    LED_Init_Expect();
    Digital_Init_Expect();
    AnalogConductor_Init_Expect();
    Executor_Init();
}

// void test_Executor_Exec_should_AlwaysReturnTrue(void)
// {
//     Digital_GetBits_IgnoreAndReturn(0x00);
//     Analog_GetReading_IgnoreAndReturn(0x0);
//     LED_Off_Ignore();
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     TEST_ASSERT_TRUE(Executor_Exec());
//     TEST_ASSERT_TRUE(Executor_Exec());
//     TEST_ASSERT_TRUE(Executor_Exec());
//     TEST_ASSERT_TRUE(Executor_Exec());
// }

// void test_Executor_Exec_should_ToggleLed0_when_Digital0IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn(0x01);
   
//     LED_Toggle_Expect(LED0);
//     LED_Off_Expect(LED1);
//     LED_Off_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed0_when_Digital1IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn(0x02);
//     LED_Toggle_Expect(LED0);
//     LED_Off_Expect(LED1);
//     LED_Off_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed0And1_when_Digital0And1IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn(0x03);
//     LED_Toggle_Expect(LED0);
//     LED_Off_Expect(LED1);
//     LED_Off_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_NotToggleLed0_when_Digital0And1IsLow(void)
// {
//     Digital_GetBits_ExpectAndReturn(0x00);
//     AllExpectLedOff();
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed1_when_Digital2IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn((1 << 2));
//     LED_Off_Expect(LED0);
//     LED_Toggle_Expect(LED1);
//     LED_Off_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed1_when_Digital3IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn((1 << 3));
//     LED_Off_Expect(LED0);
//     LED_Toggle_Expect(LED1);
//     LED_Off_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed1_when_Digital2And3IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn((0x3 << 2));
//     LED_Off_Expect(LED0);
//     LED_Toggle_Expect(LED1);
//     LED_Off_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_NotToggleLed1_when_Digital2And3IsLow(void)
// {
//     Digital_GetBits_ExpectAndReturn(0x0);
    
//     AllExpectLedOff();
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed2_when_Digital4IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn((1 << 4));
//     LED_Off_Expect(LED0);
//     LED_Off_Expect(LED1);
//     LED_Toggle_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
    
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed2_when_Digital5IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn((1 << 5));
//     LED_Off_Expect(LED0);
//     LED_Off_Expect(LED1);
//     LED_Toggle_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

// void test_Executor_Exec_should_ToggleLed2_when_Digital4And5IsHigh(void)
// {
//     Digital_GetBits_ExpectAndReturn((0x3 << 4));
//     LED_Off_Expect(LED0);
//     LED_Off_Expect(LED1);
//     LED_Toggle_Expect(LED2);
//     Analog_ReadingReady_IgnoreAndReturn(0);

//     Executor_Exec();
// }

// void test_Executor_Exec_should_NotToggleLed2_when_Digital4And5IsLow(void)
// {
//     Digital_GetBits_ExpectAndReturn(0x0);
//     AllExpectLedOff();
//     Analog_ReadingReady_IgnoreAndReturn(0);
//     Executor_Exec();
// }

void test_Executor_Exec_should_ToggleLED1IfAdc0HigherthanAdc1(void)
{
    AllExpectLedOff();
    Digital_GetBits_IgnoreAndReturn(0x0);
    Analog_ReadingReady_ExpectAndReturn(TRUE);
    
    
    expectReadings(5, 3, 0, 0, 0, 0);
    LED_On_Expect(LED1);
    LED_Off_Expect(LED2);
    LED_Off_Expect(LED3);
    LED_On_Expect(LED0);
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLED1IfAdc2HigherthanAdc3(void)
{
    AllExpectLedOff();
    LED_On_Expect(LED2);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED3);
 
    Digital_GetBits_IgnoreAndReturn(0x0);
    Analog_ReadingReady_ExpectAndReturn(TRUE);
    expectReadings(0, 0, 3, 2, 0, 0);
    LED_On_Expect(LED0);
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLED1IfAdc4HigherthanAdc5(void)
{
    AllExpectLedOff();
    LED_On_Expect(LED3);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);
    Digital_GetBits_IgnoreAndReturn(0x0);
    Analog_ReadingReady_ExpectAndReturn(TRUE);
    expectReadings(0, 0, 0, 0, 10, 9);
    LED_On_Expect(LED0);
    Executor_Exec();
}