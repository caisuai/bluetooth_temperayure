#include "farmState.h"

FarmState farmState;
FarmSafeRange farmSafeRange;

void EnvSafeRange_Init(){
	//ÎÂ¶È·¶Î§£º10-30
	farmSafeRange.maxtemperature=30;
	farmSafeRange.mintemperature=10;
	//Êª¶È·¶Î§£º20-70
	farmSafeRange.maxhumidity=70;
	farmSafeRange.minhumidity=20;
	
}
