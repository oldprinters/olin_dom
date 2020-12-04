#include "OneRled.h"
#include "ArOneLed.h"
#include "OneLed.h"

/*
ЖЕЛТЫЙ фиолетовый - кнопка	D2
ораанжевый кор. - над кнопкой - 4 D4
оранжевый зеленый 1 эт. хол D3
красный фиолетовый 1 этаж 2 D5
оранжевый синий 2 этаж мал. комн. D6
желтый коричневый 2 этаж болш. комн. 1 D7
желтый синий 2 этаж бол. комн. 2 D9
черный зеленый и черный фиолетовый крыльцо D10, D11
IR D12
*/
#define T_IBLINK 100
#define LED_BLINK 4

const int MAX_LED{ 7 };
const int BUTTON{ 2 };
const int IR{ 12 };

volatile bool flag;
bool stsLedTest{ 0 };
enum class StateHome { OFF, IR, MANUAL, AUTO, COUNT };
StateHome stateHome{ StateHome::IR };
bool irStat{};	// состояние в режиме IR

const int arPins[MAX_LED]{ 3, 5, 6, 7, 9, 10, 11 };
ArOneLed arOneLed(static_cast<const int*>(arPins), MAX_LED);

int sizeAr{};			//размер массива ручных режимов
int nPosArray{};		//номер позиции в массиве

int nIBlink{};

int arModeManual[][MAX_LED]{
	{255, 255, 255, 255, 255, 255, 255},
	{0, 0, 0, 0, 0, 255, 255},
	{255, 255, 0, 0, 0, 0, 0},
	{255, 0, 255, 0, 0, 0, 0},
	{0, 255, 0, 255, 255, 0, 0},
	{0, 0, 255, 0, 255, 0, 0},
	{0, 0, 80, 0, 80, 0, 0},
	{0, 0, 255, 0, 0, 0, 0},
	{100, 100, 0, 150, 150, 0, 0},
	{0, 0, 255, 255, 0, 100, 100},
};

Timer timerIr(240000);
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
		digitalWrite(LED_BLINK, nBlink % 2);
		delay(T_IBLINK);
	}
	digitalWrite(LED_BLINK, LOW);
}
//******************************************
void setup() {
//	Serial.begin(9600);
	sizeAr = sizeof(arModeManual) / sizeof(arModeManual[0]);	//число ручных режимов
	pinMode(IR, INPUT);
	pinMode(BUTTON, INPUT);
	pinMode(LED_BLINK, OUTPUT);
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
				iBlink(3);
			}
			else {
				arOneLed.setDims(arModeManual[++nPosArray]);
			}
			break;
		case StateHome::IR:
			stateHome = StateHome::OFF; 
			arOneLed.setStatic();
			iBlink(2);
			arOneLed.setOFF();
			break;
		}
	}
	
	if (stateHome == StateHome::IR) {
		if (timerIr.getTimer()) {
			if (digitalRead(IR)) {
				if (!irStat) {				//находимся в режиме IR
					arOneLed.setRandom();	//??????????????????????????
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
