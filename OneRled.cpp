// 
// 
// 

#include "OneRled.h"

void OneRled::cycle()
{
	if (rTimer.getTimer()) {
		int e = random(10);
		e *= e;
		e *= (-1 * random(0,2) ? 1 : -1);
		e += 100;
		setDim(e);
		rTimer.setTimer(random(2000, 10000));
	}
	OneLed::cycle();
}

