#include "Core.h"
#include "unity.h"
#include "system_LPC17xx.h"
#include "LPC1768.h"
#include "LED.h"   
 


void setUp(void)
{
    LED_Init();
}

void tearDown(void)
{
}

void helperUpdatePin(void)
{
    LPC_GPIO1->FIOPIN |=  LPC_GPIO1->FIOSET;
    LPC_GPIO1->FIOPIN &= ~LPC_GPIO1->FIOCLR;
    LPC_GPIO1->FIOSET = 0;
    LPC_GPIO1->FIOCLR = 0;
}

void test_LED_Init_should_ConfigureRegistersOfAllLEDs(void)
{
    LPC_GPIO1->FIOSET = 0;
    LPC_GPIO1->FIODIR = 0;
    LPC_PINCON->PINSEL3  = 0xFFFFFFFF;
    LPC_PINCON->PINMODE3 = 0xFFFFFFFF;

    LED_Init();

    TEST_ASSERT_EQUAL_HEX(0xFFFF30CF, LPC_PINCON->PINSEL3);
    TEST_ASSERT_EQUAL_HEX(0xFFFF30CF, LPC_PINCON->PINMODE3);
    TEST_ASSERT_EQUAL_HEX(0x00B40000, LPC_GPIO1->FIODIR);
    TEST_ASSERT_EQUAL_HEX(0x00B40000, LPC_GPIO1->FIOSET);
}

void test_LED_Toggle_should_ToggleTheCorrectOutput(void)
{
    LPC_GPIO1->FIOSET = 0;
    LPC_GPIO1->FIOCLR = 0;
    LPC_GPIO1->FIOPIN = 0;

    LED_Init();

    TEST_ASSERT_EQUAL_HEX(0x00B40000, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL_HEX(0x00000000, LPC_GPIO1->FIOCLR);
    helperUpdatePin();

    LED_Toggle(LED0);

    TEST_ASSERT_EQUAL_HEX(0x00000000, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL_HEX(0x00040000, LPC_GPIO1->FIOCLR);
    helperUpdatePin();

    LED_Toggle(LED0);

    TEST_ASSERT_EQUAL_HEX(0x00040000, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL_HEX(0x00000000, LPC_GPIO1->FIOCLR);
    helperUpdatePin();

    LED_Toggle(LED2);

    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL((1 << 21), LPC_GPIO1->FIOCLR);
    helperUpdatePin();

    LED_Toggle(LED2);
    TEST_ASSERT_EQUAL((1 << 21), LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOCLR);

}

void test_LED_Toggle_should_NotToggleOutputWithInvalidLEDPin(void)
{
    LPC_GPIO1->FIOSET = 0;
    LPC_GPIO1->FIOCLR = 0;
    LPC_GPIO1->FIOPIN = 0;

    LED_Init();
    helperUpdatePin();

    LED_Toggle(300);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOCLR);
    helperUpdatePin();

    LED_Toggle(-3);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOCLR);
}

void test_LED_On_should_EnableTheCorrectOutput(void)
{
    LPC_GPIO1->FIOSET = 0;
    LPC_GPIO1->FIOCLR = 0;
    LPC_GPIO1->FIOPIN = 0;
    
    LED_On(LED3);
    TEST_ASSERT_EQUAL(1 << 23, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOCLR);

}

void test_LED_Of_should_DisableTheCorrectOutput(void)
{
    LPC_GPIO1->FIOSET = 0;
    LPC_GPIO1->FIOCLR = 0;
    LPC_GPIO1->FIOPIN = 0;
    
    LED_Off(LED3);
    TEST_ASSERT_EQUAL(0, LPC_GPIO1->FIOSET);
    TEST_ASSERT_EQUAL(1 << 23, LPC_GPIO1->FIOCLR);
}