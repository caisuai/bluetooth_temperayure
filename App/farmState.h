#ifndef __FARMSTATE_H__
#define __FARMSTATE_H__

#include "cmsis_os2.h"

#include <stdint.h>

typedef struct {
	float temperature;
	float humidity;
	uint8_t waterState;
}FarmState;

typedef struct {
	float maxtemperature;
	float mintemperature;
	float maxhumidity;
	float minhumidity;
}FarmSafeRange;


extern FarmState farmState;
extern FarmSafeRange farmSafeRange;

void EnvSafeRange_Init(void);
	
#endif
