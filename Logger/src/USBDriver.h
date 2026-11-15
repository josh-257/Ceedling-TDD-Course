#ifndef USBDRIVER_H
#define USBDRIVER_H

#include <stdbool.h>

bool USBDriver_OkayToRead(void);
char USBDriver_GetChar(void);

#endif // USBDRIVER_H
