#include "cmsis_os2.h"
#include "farmState.h"
#include "screen.h"
#include "../BSP/key/key.h"
#include "../BSP/knob/knob.h"
#include <stdint.h>

//±à¼­ãÐÖµÊýÖµ

void EditRangeValue(RangeEditIndex index, int8_t direction) {
	switch(index){
		case RANGE_EDIT_TEMPERATURE_MIN:
			if(farmSafeRange.mintemperature+0.1*direction<farmSafeRange.maxtemperature){
				farmSafeRange.mintemperature+=0.1*direction;
			}
			break;
		case RANGE_EDIT_TEMPERATURE_MAX:
			if(farmSafeRange.maxtemperature+0.1*direction>farmSafeRange.mintemperature){
				farmSafeRange.maxtemperature+=0.1*direction;
			}
			break;
		case RANGE_EDIT_HUMIDITY_MIN:
			if(farmSafeRange.minhumidity+0.1*direction<farmSafeRange.maxhumidity){
				farmSafeRange.minhumidity+=0.1*direction;
			}
			break;
		case RANGE_EDIT_HUMIDITY_MAX:
			if(farmSafeRange.maxhumidity+0.1*direction>farmSafeRange.minhumidity){
				farmSafeRange.maxhumidity+=0.1*direction;
			}
			break;
		default:
			break;
	}
}

extern void StartInputTask(void *argument){
	Knob_Init();
	for(;;){
		if(isKey1Clicked()){
			ScreenPage_NextPage();
		}
		if(pageIndex==PAGE_RANGE){
			if(isKey3Clicked()){
				RangeEditState_Toggle();
			}
			KnobDirection direction=Knob_IsRotating();
			if(rangeEditState==RANGE_EDIT_STATE_NORMAL){
				if(direction==KNOB_DIR_LEFT){
					RangeEditIndex_Prev();
				}else if(direction==KNOB_DIR_RIGHT){
					RangeEditIndex_Next();
				}
			}else if(rangeEditState==RANGE_EDIT_STATE_EDITING){
				if(direction==KNOB_DIR_LEFT){
					EditRangeValue(rangeEditIndex,-1);
				}else if(direction==KNOB_DIR_RIGHT){
					EditRangeValue(rangeEditIndex,1);
				}
			}
		}
		
		
		osDelay(10);
	}
}
