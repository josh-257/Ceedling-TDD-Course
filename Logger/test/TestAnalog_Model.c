
#include "unity.h"
#include "MockFilter.h"
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
    AnalogModel_Init();

    Filter_AddVal_ExpectAndReturn(0x0, 0x1234, 0x4321);
    AnalogModel_AddReading(0, 0x1234);

    TEST_ASSERT_EQUAL_HEX16(0x4321, AnalogModel_GetChannel(0));
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(1));
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(NUM_ADC_CHANNELS - 1));

}

void test_AnalogModel_GetChannel_should_ReturnLatestDataMultipleChannels(void)
{
    AnalogModel_Init();

    Filter_AddVal_ExpectAndReturn(0x0, 0x1234, 0x1234);
    Filter_AddVal_ExpectAndReturn(0x0, 0x567, 0x567);
    Filter_AddVal_ExpectAndReturn(0x0, 0x123, 0x123);

    AnalogModel_AddReading(0, 0x1234);
    AnalogModel_AddReading(2, 0x567);
    AnalogModel_AddReading(3, 0x123);

    
    
    TEST_ASSERT_EQUAL_HEX16(0x1234, AnalogModel_GetChannel(0));
    TEST_ASSERT_EQUAL_HEX16(0x567, AnalogModel_GetChannel(2));
    TEST_ASSERT_EQUAL_HEX16(0x123, AnalogModel_GetChannel(3));

}

void test_AnalogModel_GetChannel_should_NotIgnoreInvalidChannels(void)
{
    AnalogModel_Init();

    Filter_AddVal_ExpectAndReturn(0x0, 0x1234, 0x1234);
    AnalogModel_AddReading(0, 0x1234);

    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(300));
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(1));
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(NUM_ADC_CHANNELS - 1));
}

void test_AnalogModel_GetChannel_should_DealsWithStaleValues(void)
{
    AnalogModel_Init();

    Filter_AddVal_ExpectAndReturn(0x0, 11, 11);
    Filter_AddVal_ExpectAndReturn(0x0, 22, 22);

    AnalogModel_AddReading(0, 11);
    AnalogModel_AddReading(1, 22);

    TEST_ASSERT_EQUAL_HEX16(11, AnalogModel_GetChannel(0));
    TEST_ASSERT_EQUAL_HEX16(22, AnalogModel_GetChannel(1));
    TEST_ASSERT_EQUAL_HEX16(0, AnalogModel_GetChannel(2));

    Filter_AddVal_ExpectAndReturn(22, 222, 222);
    Filter_AddVal_ExpectAndReturn(0x0, 333, 333);

    AnalogModel_AddReading(1, 222);
    AnalogModel_AddReading(2, 333);

    TEST_ASSERT_EQUAL_HEX16(11, AnalogModel_GetChannel(0));
    TEST_ASSERT_EQUAL_HEX16(222, AnalogModel_GetChannel(1));
    TEST_ASSERT_EQUAL_HEX16(333, AnalogModel_GetChannel(2));
}