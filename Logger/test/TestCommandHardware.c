
#include "MockUSBDriver.h"
#include "unity.h"
#include "MockParser.h"
#include "CommandHardware.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_CommandHardware_CheckForMsg_should_ReturnNoneYet_When_NoBytesAvailable(void)
{
    MESSAGE_T msg = {0};
    USBDriver_OkayToRead_ExpectAndReturn(FALSE);

    TEST_ASSERT_EQUAL(STATUS_NONE_YET, CommandHardware_CheckForMsg(&msg));
}

void test_CommandHardware_CheckForMsg_should_GetCharAndAddToPacker_When_BytesAvailable(void)
{
    MESSAGE_T msg = {0};
    USBDriver_OkayToRead_ExpectAndReturn(TRUE);
    USBDriver_GetChar_ExpectAndReturn('V');
    Parser_AddChar_ExpectAndReturn('V', NULL);

    TEST_ASSERT_EQUAL(STATUS_NONE_YET, CommandHardware_CheckForMsg(&msg));
}

void test_CommandHardware_CheckForMsg_should_FillOutMsgStruct_When_ZeroLenPacketComplete(void)
{
    char * cmd = "[V0]";
    MESSAGE_T msg = {0};

    USBDriver_OkayToRead_ExpectAndReturn(TRUE);
    USBDriver_GetChar_ExpectAndReturn(']');
    Parser_AddChar_ExpectAndReturn(']', cmd);

    TEST_ASSERT_EQUAL(STATUS_OK, CommandHardware_CheckForMsg(&msg));
    TEST_ASSERT_EQUAL_HEX8('V', msg.cmd);
    TEST_ASSERT_EQUAL_INT8(0, msg.len);
}


