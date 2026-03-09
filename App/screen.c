#include "screen.h"

ScreenPage pageIndex=PAGE_HOME;

void ScreenPage_NextPage(){
	pageIndex++;
	if(pageIndex==PAGE_END){
		pageIndex=PAGE_HOME;
	}
}

RangeEditIndex rangeEditIndex=RANGE_EDIT_TEMPERATURE_MIN;

void RangeEditIndex_Next(){
	rangeEditIndex++;
	if(rangeEditIndex==RANGE_EDIT_HUMIDITY_MAX){
		rangeEditIndex=RANGE_EDIT_TEMPERATURE_MIN;
	}
}

void RangeEditIndex_Prev(){
	if(rangeEditIndex==0){
		rangeEditIndex=RANGE_EDIT_END-1;
	}else{
		rangeEditIndex--;
	}
}

RangeEditState rangeEditState = RANGE_EDIT_STATE_NORMAL;

void RangeEditState_EnterEditing(){
	rangeEditState=RANGE_EDIT_STATE_EDITING;
}

void RangeEditState_QuitEditing(){
	rangeEditState=RANGE_EDIT_STATE_NORMAL;
}

void RangeEditState_Toggle(){
	if(rangeEditState==RANGE_EDIT_STATE_NORMAL){
		RangeEditState_EnterEditing();
	}else{
		RangeEditState_QuitEditing();
	}
}

