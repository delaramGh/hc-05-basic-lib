#ifndef HC05__LIB__
#define HC05__LIB__

#include "main.h"
#include "usart.h"
#include <string.h>


#define HC05_UARTh  (&huart2)
#define HC05_EN_PIN  GPIO_PIN_11
#define HC05_EN_PORT GPIOB


void HC05_ClearData(void);

void HC05_test(char* s);

HAL_StatusTypeDef HC05_IsDeviceReady(uint16_t timeout);

HAL_StatusTypeDef HC05_Reset(uint16_t timeout);

//HAL_StatusTypeDef HC05_uartSetting(char* parameters, uint16_t timeout);



#endif

