// OneLed.h

#ifndef _ONELED_h
#define _ONELED_h
#include "Timer.h"

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum class StatLed { OFF, ON, BLINK, DIM };

class OneLed:	public Timer
{
	const int pin;
	int level{ 0 };
	int levelDim{ 0 };
	StatLed statLed{ StatLed::OFF };
public:
	OneLed(int p): Timer(10), pin(p) { pinMode(pin, OUTPUT); }
	int getPin() { return pin; }
	void setStat(StatLed stat);
	void setDim(int l);
	virtual void cycle();
};

#endif

