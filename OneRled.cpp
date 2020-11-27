// 
// 
// 

#include "OneRled.h"

void OneRled::cycle()
{
	if (rTimer.getTimer()) {
		setDim(random(155));
		rTimer.setTimer(random(2000, 10000));
	}
	OneLed::cycle();
}

