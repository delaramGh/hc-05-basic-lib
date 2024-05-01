#include "my_hc05_lib.h"

// GLOBAL VARIABLES
uint8_t rData_1bit[1], rData[50];


void HC05_test(char* s)
{
	HC05_ClearData();
	HAL_UART_Receive_IT(HC05_UARTh, rData_1bit, 1);
	HAL_UART_Transmit(HC05_UARTh, (uint8_t*)s, strlen(s), 200);
}



HAL_StatusTypeDef HC05_IsDeviceReady(uint16_t timeout)
{
	HC05_ClearData();
	HAL_GPIO_WritePin(HC05_EN_PORT, HC05_EN_PIN, GPIO_PIN_SET);
	HAL_Delay(50);
	
	HAL_UART_Receive_IT(HC05_UARTh, rData_1bit, 1);
	HAL_UART_Transmit(HC05_UARTh, (uint8_t*)"AT\r\n", strlen("AT\r\n"), 200);
	
	uint32_t Tickstart = HAL_GetTick();
	
	while(strstr((char*)rData, "OK") == 0)
		if((HAL_GetTick() - Tickstart) > timeout) return HAL_TIMEOUT;
	
	return HAL_OK;
}



HAL_StatusTypeDef HC05_uartSetting(char* parameters, uint16_t timeout)
{
	HC05_ClearData();
	HAL_UART_Receive_IT(HC05_UARTh, rData_1bit, 1);
	char buffer[40];
	sprintf(buffer, "AT+UART%s\r\n", parameters);
	HAL_UART_Transmit(HC05_UARTh, (uint8_t*)buffer, strlen(buffer), 200);
	
	uint32_t Tickstart = HAL_GetTick();
	
	while(strstr((char*)rData, "OK") == 0)
		if((HAL_GetTick() - Tickstart) > timeout) return HAL_TIMEOUT;
	
	return HAL_OK;
}


HAL_StatusTypeDef HC05_Reset(uint16_t timeout)
{
	HC05_ClearData();
	HAL_UART_Receive_IT(HC05_UARTh, rData_1bit, 1);
	HAL_UART_Transmit(HC05_UARTh, (uint8_t*)"AT+RESET\r\n", strlen("AT+RESET\r\n"), 200);
	
	uint32_t Tickstart = HAL_GetTick();
	
	while(strstr((char*)rData, "OK") == 0)
		if((HAL_GetTick() - Tickstart) > timeout) return HAL_TIMEOUT;
	
	HAL_GPIO_WritePin(HC05_EN_PORT, HC05_EN_PIN, GPIO_PIN_RESET);
	HAL_Delay(10);
	
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