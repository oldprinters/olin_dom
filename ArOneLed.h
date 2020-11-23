// ArOneLed.h

#ifndef _ARONELED_h
#define _ARONELED_h
#include "OneLed.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class ArOneLed
{
	const int* arP{};
	const int nPins{};
	bool on{ true };
	OneLed** ar;
public:
	ArOneLed( const int* arp, const int n);
	void init();
	void setDims(int* arMode);
	void setON();
	void setOFF();
	void setBlink();
	void setRandom();
	void setStatic();	//выход из режима Random
	void cycle();
};

#endif

