#include "cmsis_os.h"
#include "main.h"
#include "stm32f1xx_hal_uart.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "freertos.h"

void StartBLETask(void *argument){
	for(;;){
		char *msg;
		osMessageQueueGet(BLEQueueHandle,&msg,NULL,osWaitForever);
		if(msg!=NULL){
			HAL_UART_Transmit_DMA(&huart3,(uint8_t*)msg,strlen(msg));
			while(1){
				if(HAL_UART_GetState(&huart3)==HAL_UART_STATE_READY){
					break;
				}
				osDelay(1);
			}
			vPortFree(msg);
		}
	}
}
