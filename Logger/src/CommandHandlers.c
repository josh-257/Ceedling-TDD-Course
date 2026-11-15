#include "CommandHandlers.h"

STATUS_T CommandHandlers_Version(MESSAGE_T *msg)
{
    msg->cmd = '1';
    return STATUS_OK;
}