#include "../BSP/aht20/aht20.h"
#include "cmsis_os2.h"
#include "freertos.h"
#include "main.h"
#include "../BSP/pump/pump.h"
#include "farmState.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

static void floatToIntDec(float value,int *intpart,int *decpart){
	*intpart=(int)value;
	float decimal=value=value-(float)(*intpart);
	if(decimal<0){
		decimal=-decimal;
	}
	*decpart=(int)(decimal*10+0.5f);
	if(*decpart>10){
		*decpart=0;
		(*intpart)++;
	}else if(*decpart<0){
		*decpart=0;
	}
}

static void SendWarningFloat(const char *reason,float value){
	char *msg = pvPortMalloc(100); 
	if(msg==NULL){
		return; 
	}
	int minInt,minDec;
	floatToIntDec(value,&minInt,&minDec);
	snprintf(msg,100,"{\"type\":\"warning\",\"reason\":\"%s\", \"value\":%d.%d}", reason, minInt, minDec);
	osMessageQueuePut(BLEQueueHandle,&msg,NULL,0);
}

static uint8_t ChackRangeFloat(float value,float max,float min ,const char *minReason,const char *maxReason){
	uint8_t warning=0;
	if(value <min){
		SendWarningFloat(minReason,value);
		warning=1;
	}
	if(value >max){
		SendWarningFloat(maxReason,value);
		warning=1;
	}
	return warning;
}

void StartsensorTask(void *argument){
	EnvSafeRange_Init();
	
	osMutexAcquire(i2c1MutexHandle, osWaitForever);
    AHT20_Init();
    osMutexRelease(i2c1MutexHandle);
	
	
	for(;;){
		osMutexAcquire(i2c1MutexHandle,osWaitForever);
		AHT20_Read(&farmState.temperature,&farmState.humidity);
		osMutexRelease(i2c1MutexHandle);
		
		if(farmState.humidity<farmSafeRange.minhumidity){
			Pump_On();
			farmState.waterState=1;
		}else{
			Pump_Off();
			farmState.waterState=0;
		}
		//判断是否低于/高于阈值
		
		uint8_t warning=0;
		char *msg;
		warning+=ChackRangeFloat(farmState.temperature,farmSafeRange.maxtemperature,farmSafeRange.mintemperature,"minReason","maxReason");
		warning+=ChackRangeFloat(farmState.humidity, farmSafeRange.minhumidity, farmSafeRange.maxhumidity, "humidity_low", "humidity_high");
		if(warning<=0){
			snprintf(msg,100,"{\"type\":\"ok\",\"temperature\":\"%.1f\", \"humidity\":%.1f}",farmState.temperature,farmState.humidity);
			osMessageQueuePut(BLEQueueHandle,&msg,NULL,0);
		}
		
		osDelay(1000);
	}
}
