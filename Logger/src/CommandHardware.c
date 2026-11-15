#include "CommandHardware.h"
#include "USBDriver.h"
#include "Parser.h"

STATUS_T CommandHardware_CheckForMsg(MESSAGE_T* msg)
{
    if(USBDriver_OkayToRead())
    {
        char byte = USBDriver_GetChar();
        char *ParsedPacket = Parser_AddChar(byte);
        if(ParsedPacket != NULL)
        {
            msg->cmd = ParsedPacket[1];
            msg->len = (ParsedPacket[2] - '0');
            return STATUS_OK;
        }
    }
    return STATUS_NONE_YET;
}