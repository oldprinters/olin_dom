// 
// 
// 

#include "OneLed.h"
#define MAX_LEVEL 255

//*************************************************
//управление димером
void OneLed::setDim(int l) {
	levelDim = l; 
//	Serial.println(levelDim);
}
//*********************************************
void OneLed::setStat(StatLed stat) {
	statLed = stat; 
	switch (statLed) {
		case StatLed::OFF:levelDim = 0; break;
		case StatLed::BLINK:
		case StatLed::ON:levelDim = MAX_LEVEL; break;
		case StatLed::DIM:break;
	}
}
//*************************************
void OneLed::cycle() {
	if (level != levelDim) {
		if (getTimer()) {
			setTimer();
			level += (level < levelDim? 1: -1);
		}
	}
	analogWrite(pin, level);
}

