// ����� ��������� �������� �����������
#include "ArOneLed.h"
#include "OneRled.h"

//****************************************************
ArOneLed::ArOneLed(const int* arp, const int n):arP(arp), nPins(n) {
	init();
}
//****************************************************
void ArOneLed::init() {
	ar = new OneLed * [nPins];
	for (int i = 0; i < nPins; ++i) {
		ar[i] = new OneLed(arP[i]);
	}
}
//****************************************************
void ArOneLed::setDims(int* arDims) {
	for (int i{}; i < nPins; ++i) {
		ar[i]->setDim(arDims[i]);
	}
}
//****************************************************
void ArOneLed::setON() {
	for (int i{}; i < nPins; ++i) {
		ar[i]->setStat(StatLed::ON);
	}
}
//****************************************************
void ArOneLed::setOFF() {
	for (int i{}; i < nPins; ++i) {
		ar[i]->setStat(StatLed::OFF);
	}
}
//****************************************************
void ArOneLed::setBlink() {
	for (int i{}; i < nPins; ++i) {
		ar[i]->setStat(StatLed::BLINK);
	}
}
//****************************************************
void ArOneLed::setStatic() {
	delete[] ar;
	init();
}
//****************************************************
void ArOneLed::setRandom() {
	for (int i{}; i < nPins; ++i) {
		delete ar[i];
		ar[i] = new OneRled(arP[i]);
	}
}
//****************************************************
void ArOneLed::cycle() {
	for (int i{}; i < nPins; ++i) {
		ar[i]->cycle();
	}
}

