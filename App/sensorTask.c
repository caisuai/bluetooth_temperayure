#include "../BSP/aht20.h"
#include "cmsis_os2.h"
#include "freertos.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>


void StartsensorTask(void *argument){
	AHT20_Init();
	float temperature,humidity;
	
	for(;;){
		AHT20_Read(&temperature,&humidity);
		char *msg = pvPortMalloc(64);
		if(msg!=NULL){
			snprintf(msg, 64, "Temp=%.1f, Hum=%.1f\r\n", temperature, humidity);
//			snprintf(msg, 100, "ÎÂ¶È£º%.lf ¡æ,Êª¶È: %.lf %%\r\n", temperature, humidity);
			osMessageQueuePut(BLEQueueHandle,&msg,0,0);
		}
		osDelay(1000);
	}
}
