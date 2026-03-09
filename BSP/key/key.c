#include "key.h"



uint8_t isKey1Clicked(){
	static uint8_t pressed=0;
	if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET && !pressed){
		osDelay(10);
		if(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET){
			pressed=1;
			return 1;
		}
	}
	if(pressed && !(HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)==GPIO_PIN_RESET)){
		pressed=0;
	}
	return 0;
}

uint8_t isKey3Clicked(){
	static uint8_t pressed=0;
	if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET && !pressed){
		osDelay(10);
		if(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET){
			pressed=1;
			return 1;
		}
	}
	if(pressed && !(HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)==GPIO_PIN_RESET)){
		pressed=0;
	}
	return 0;
}
