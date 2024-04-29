#include "my_hc05_lib.h"

// GLOBAL VARIABLES
uint8_t rData_1bit[1], rData[50];




HAL_StatusTypeDef HC05_IsDeviceReady(uint16_t timeout)
{
	HAL_UART_Receive_IT(HC05_UARTh, rData_1bit, 1);
	HAL_UART_Transmit(HC05_UARTh, (uint8_t*)"AT\r\n", strlen("AT\r\n"), 200);
	
	uint32_t Tickstart = HAL_GetTick();
	
	while(strstr((char*)rData, "OK") == 0)
		if((HAL_GetTick() - Tickstart) > timeout) return HAL_TIMEOUT;
	
	return HAL_OK;
}


void HC05_ClearData(void)
{
	for(uint8_t i=0; i<50; i++)
		rData[i] = 0;
	rData_1bit[0] = 0;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == HC05_UARTh->Instance)
	{
		strcat((char*)rData, (char*)rData_1bit);
		
		
		HAL_UART_Receive_IT(HC05_UARTh, rData_1bit, 1);
	}
}