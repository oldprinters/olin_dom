// 
// 
// 

#include "OneRled.h"

void OneRled::cycle()
{
	if (rTimer.getTimer()) {
		setDim(random(155));
		rTimer.setTimer(random(8000, 15000));
	}
	OneLed::cycle();
}

