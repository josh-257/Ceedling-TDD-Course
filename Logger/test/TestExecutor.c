

#include "unity.h"
#include "MockLED.h"
#include "MockDigital.h"
#include "Executor.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Executor_Init_should_InitializeAllSubsystems(void)
{
    LED_Init_Expect();
    Digital_Init_Expect();
    Executor_Init();
}

void test_Executor_Exec_should_AlwaysReturnTrue(void)
{
    Digital_GetBits_IgnoreAndReturn(0x00);
    LED_Off_Ignore();

    TEST_ASSERT_TRUE(Executor_Exec());
    TEST_ASSERT_TRUE(Executor_Exec());
    TEST_ASSERT_TRUE(Executor_Exec());
    TEST_ASSERT_TRUE(Executor_Exec());
}

void test_Executor_Exec_should_ToggleLed0_when_Digital0IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn(0x01);
    LED_Toggle_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);

    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed0_when_Digital1IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn(0x02);
    LED_Toggle_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);

    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed0And1_when_Digital0And1IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn(0x03);
    LED_Toggle_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);
    Executor_Exec();
}

void test_Executor_Exec_should_NotToggleLed0_when_Digital0And1IsLow(void)
{
    Digital_GetBits_ExpectAndReturn(0x00);
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed1_when_Digital2IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn((1 << 2));
    LED_Off_Expect(LED0);
    LED_Toggle_Expect(LED1);
    LED_Off_Expect(LED2);
    
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed1_when_Digital3IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn((1 << 3));
    LED_Off_Expect(LED0);
    LED_Toggle_Expect(LED1);
    LED_Off_Expect(LED2);
    
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed1_when_Digital2And3IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn((0x3 << 2));
    LED_Off_Expect(LED0);
    LED_Toggle_Expect(LED1);
    LED_Off_Expect(LED2);
    
    Executor_Exec();
}

void test_Executor_Exec_should_NotToggleLed1_when_Digital2And3IsLow(void)
{
    Digital_GetBits_ExpectAndReturn(0x0);
    
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);
    
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed2_when_Digital4IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn((1 << 4));
    
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Toggle_Expect(LED2);
    
    
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed2_when_Digital5IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn((1 << 5));
    
    
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Toggle_Expect(LED2);
    Executor_Exec();
}

void test_Executor_Exec_should_ToggleLed2_when_Digital4And5IsHigh(void)
{
    Digital_GetBits_ExpectAndReturn((0x3 << 4));
    
    
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Toggle_Expect(LED2);
    

    Executor_Exec();
}

void test_Executor_Exec_should_NotToggleLed2_when_Digital4And5IsLow(void)
{
    Digital_GetBits_ExpectAndReturn(0x0);
    
    LED_Off_Expect(LED0);
    LED_Off_Expect(LED1);
    LED_Off_Expect(LED2);

    Executor_Exec();
}