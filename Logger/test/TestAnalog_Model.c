
#include "unity.h"
#include "Analog_Model.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_Analog_GetChannel_should_ReturnZeroWhenChannelIllegal(void)
{
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(NUM_ADC_CHANNELS));
}

void test_Analog_GetChannel_should_ReturnZeroWhenNoValueCapturedYet(void)
{
    AnalogModel_Init();
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(0));
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(NUM_ADC_CHANNELS - 1));
}

void test_AnalogModel_GetChannel_should_ReturnLatestData(void)
{
    TEST_IGNORE_MESSAGE("Need to implement");
}
