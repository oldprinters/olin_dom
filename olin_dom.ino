#include "OneRled.h"
#include "ArOneLed.h"
#include "OneLed.h"

#define T_IBLINK 100

const int MAX_LED{ 8 };
const int LED3{ 3 };
const int LED4{ 4 };
const int BUTTON{ 2 };
const int IR{ 12 };

volatile bool flag;
bool stsLedTest{ 0 };
enum class StateHome { OFF, AUTO, MANUAL, IR, COUNT };
StateHome stateHome = StateHome::AUTO;
bool irStat{};	// состояние в режиме IR

const int arPins[MAX_LED]{ 3, 4, 5, 6, 7, 8, 9, 10 };
ArOneLed arOneLed(static_cast<const int*>(arPins), MAX_LED);

int sizeAr{};			//размер массива ручных режимов
int nPosArray{};		//номер позиции в массиве

int nIBlink{};

int arModeManual[][MAX_LED]{
	{255, 0, 0, 0, 0, 0, 0, 0},
	{0, 255, 0, 0, 0, 0, 0, 0},
	{0, 0, 255, 0, 0, 0, 0, 0},
	{0, 0, 0, 255, 0, 0, 0, 0},
	{0, 0, 0, 0, 255, 0, 0, 0},
	{0, 0, 0, 0, 0, 255, 0, 0},
	{0, 0, 0, 0, 0, 0, 255, 0},
	{0, 0, 0, 0, 0, 0, 0, 255},
	{255, 255, 255, 255, 255, 255, 255, 255},
};

Timer timerIr(10000);
//***********************************
void press_button()
{
	static unsigned long millis_prev;
	if (millis() - 100 > millis_prev)
		flag = 1;
	millis_prev = millis();
}
//***************************************************************
void iBlink(int nBlink) {
	nBlink *= 2;
	for (; nBlink--;) {
		for (int j = 0; j < MAX_LED; ++j) {
			digitalWrite(arPins[j], nBlink & 1);
		}
		delay(T_IBLINK);
		for (int j = 0; j < MAX_LED; ++j) {
			digitalWrite(arPins[j], nBlink & 1 ^ 1);
		}
		delay(T_IBLINK);
	}
	for (int j = 0; j < MAX_LED; ++j) {
		digitalWrite(arPins[j], LOW);
	}
}
//******************************************
void setup() {
//	Serial.begin(9600);
	sizeAr = sizeof(arModeManual) / sizeof(arModeManual[0]);	//число ручных режимов
	pinMode(IR, INPUT);
	pinMode(BUTTON, INPUT);
	iBlink(1);
	arOneLed.setRandom();
	attachInterrupt(digitalPinToInterrupt(2), press_button, LOW);
}
//***************************************************************
void loop() {
	if (flag) {
		flag = 0;
		switch (stateHome) {
		case StateHome::OFF: 
			stateHome = StateHome::AUTO;
			arOneLed.setRandom();
			iBlink(3);
			break;
		case StateHome::AUTO: 
			stateHome = StateHome::MANUAL; 
			nPosArray = 0; 
			arOneLed.setStatic();
			arOneLed.setDims(arModeManual[nPosArray]);
			iBlink(1);
			break;
		case StateHome::MANUAL:
			if (nPosArray == sizeAr-1) {
				nPosArray = 0;
				stateHome = StateHome::IR;
				arOneLed.setRandom();
				timerIr.setTimer();
				irStat = true;
				iBlink(1);
			}
			else {
				arOneLed.setDims(arModeManual[nPosArray++]);
			}
			break;
		case StateHome::IR:
			stateHome = StateHome::OFF; 
			arOneLed.setStatic();
			iBlink(2);
			arOneLed.setOFF();
			break;
		}
//		Serial.println(static_cast<int>(stateHome));
	}
	
	if (stateHome == StateHome::IR) {
		if (timerIr.getTimer()) {
			if (digitalRead(IR)) {
				if (!irStat) {
					arOneLed.setRandom();
					irStat = true;
				}
				timerIr.setTimer();
			}
			else {
				irStat = false;
				arOneLed.setOFF();
			}

		} 
	}
	arOneLed.cycle();
}
