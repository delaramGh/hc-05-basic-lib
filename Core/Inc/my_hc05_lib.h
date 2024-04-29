#ifndef HC05__LIB__
#define HC05__LIB__

#include "main.h"
#include "usart.h"
#include <string.h>


#define HC05_UARTh  (&huart2)



HAL_StatusTypeDef HC05_IsDeviceReady(uint16_t timeout);

void HC05_ClearData(void);

#endif

