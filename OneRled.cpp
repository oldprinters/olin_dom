// 
// 
// 

#include "OneRled.h"

void OneRled::cycle()
{
	if (rTimer.getTimer()) {
		setDim(random(255));
		rTimer.setTimer(random(3000, 15000));
	}
	OneLed::cycle();
}

