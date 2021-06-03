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
TaskHandle_t State::voltageInputHandle = NULL;
TaskHandle_t State::safetyMonitorHandle = NULL;
TaskHandle_t State::tempMonitorHandle = NULL;

StateData State::getFullState() {
	return stateData;
}

void State::setup(TaskHandle_t  dH, TaskHandle_t  vH, TaskHandle_t  sMH, TaskHandle_t tmH)
{
	displayHandle = dH;
	voltageInputHandle = vH;
	safetyMonitorHandle = sMH;
	tempMonitorHandle = tmH;
}

TaskHandle_t State::getVoltageInputHandle()
{
	return voltageInputHandle;
}

TaskHandle_t State::getTempMonitorHandle()
{
	return tempMonitorHandle;
}

TaskHandle_t State::getSafetyMonitorHandle()
{
	return safetyMonitorHandle;
}

TaskHandle_t State::getDisplayHandle()
{
	return displayHandle;
}

void State::setVoltage(double v)
{
	stateData.voltage = v;
	xTaskNotifyGive(displayHandle);
}

void State::setTemp(double t)
{
	stateData.temp = t;
	xTaskNotifyGive(displayHandle);
}

void State::setMode(const char* mode)
{
	stateData.mode = mode;
	xTaskNotifyGive(displayHandle);
}

void State::setStatus(const char* status)
{
	stateData.status = status;
	xTaskNotifyGive(displayHandle);
}