// OneRled.h

#ifndef _ONERLED_h
#define _ONERLED_h
#include "OneLed.h"
#include "Timer.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class OneRled: public OneLed
{
 protected:
	 unsigned long dT{};
	 Timer rTimer;
 public:
	 OneRled(int p):OneLed(p){}
	 void cycle() override;
};
#endif

