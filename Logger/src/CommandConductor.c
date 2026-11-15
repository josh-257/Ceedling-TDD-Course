#include "CommandConductor.h"
#include "CommandHandlers.h"
#include "CommandHardware.h"

void CommandConductor_Init(void)
{
    CommandHandlers_Init();
    CommandHardware_Init();
}

void CommandConductor_Exec(void)
{
    MESSAGE_T msg;
    CommandHardware_Exec();

    if(CommandHardware_CheckForMsg(&msg) == STATUS_OK)
    {
        if(msg.cmd == 'V')
        {
            if(CommandHandlers_Version(&msg) == STATUS_OK)
            {
                CommandHardware_SendResponse(&msg);
            }
            else
            {
                CommandHardware_SendError(&msg);
            }
        }
    }
}

