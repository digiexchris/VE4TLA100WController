#include "State.hpp"


StateData State::stateData = {
	.voltage = 50.33333,
	.current = 3.33443,
	.power = 100.3344343,
	.swr = 1.99443,
	.temp = 32.11343,
	.band = Band::b160m,
	.status = STATE_RECEIVING,
	.mode = MODE_MANUAL
};

TaskHandle_t State::displayHandle = NULL;

StateData State::getFullState() {
	return stateData;
}

void State::setup(TaskHandle_t  dH)
{
	displayHandle = dH;
}
void State::setVoltage(double v)
{
	stateData.voltage = v;
	
	xTaskNotifyGive(displayHandle);
}