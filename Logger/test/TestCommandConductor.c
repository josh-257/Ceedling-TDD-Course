#include "unity.h"
#include "MockCommandHandlers.h"
#include "MockCommandHardware.h"
#include "CommandConductor.h"

void setUp(void)
{
}

void tearDown(void)
{
}

MESSAGE_T msg;
MESSAGE_T rsp;

void test_CommandConductor_Init_ShouldInitializeSubmodules(void)
{
    CommandHardware_Init_Expect();
    CommandHandlers_Init_Expect();

    CommandConductor_Init();
}

void test_CommandConductor_Exec_should_CheckForMessages_And_DoNothingIfNone(void)
{
    CommandHardware_Exec_Expect();
    CommandHardware_CheckForMsg_ExpectAnyArgsAndReturn(STATUS_NONE_YET);

    CommandConductor_Exec();
}

void test_CommandConductor_Exec_should_CheckForMessages_And_DoNothingIfUnknown(void)
{
    msg.cmd = 'U'; //Unknown Command

    CommandHardware_Exec_Expect();
    CommandHardware_CheckForMsg_ExpectAnyArgsAndReturn(STATUS_OK);
    CommandHardware_CheckForMsg_ReturnThruPtr_msg(&msg);

    CommandConductor_Exec();
}
void test_CommandConductor_Exec_should_CheckForMessages_And_ProcessIfVersionAndReturnResponse(void)
{
    msg.cmd = 'V'; //Version Command
    rsp.cmd = 'v'; //Command to be sent
    
    CommandHardware_Exec_Expect();
    CommandHardware_CheckForMsg_ExpectAnyArgsAndReturn(STATUS_OK);
    CommandHardware_CheckForMsg_ReturnThruPtr_msg(&msg);

    CommandHandlers_Version_ExpectAndReturn(&msg, STATUS_OK);
    CommandHandlers_Version_ReturnThruPtr_msg(&rsp);
    CommandHardware_SendResponse_ExpectAndReturn(&rsp, STATUS_OK);

    CommandConductor_Exec(); 
}

void test_CommandConductor_Exec_should_CheckForMessages_And_ProcessIfVersionAndHandleErrors(void)
{
    msg.cmd = 'V'; //Version Command
    rsp.cmd = 'E'; //Command to be sent

    CommandHardware_Exec_Expect();
    CommandHardware_CheckForMsg_ExpectAnyArgsAndReturn(STATUS_OK);
    CommandHardware_CheckForMsg_ReturnThruPtr_msg(&msg);

    CommandHandlers_Version_ExpectAndReturn(&msg, STATUS_BAD_MSG);
    CommandHandlers_Version_ReturnThruPtr_msg(&rsp);
    CommandHardware_SendError_ExpectAndReturn(&rsp, STATUS_OK);

    CommandConductor_Exec(); 
}