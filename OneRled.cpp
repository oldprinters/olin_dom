// 
// 
// 

#include "OneRled.h"

void OneRled::cycle()
{
	if (rTimer.getTimer()) {
		setDim(random(180) >60? 180: 0);
		rTimer.setTimer(random(2000, 10000));
	}
	OneLed::cycle();
}

