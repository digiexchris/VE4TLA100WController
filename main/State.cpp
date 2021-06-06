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

// Special behavior for ++Band
Band operator++(Band &c) {
	
	//don't go higher than 6m
	if (c == Band::b6m)
	{
		return c;
	}
	
	c = static_cast<Band>(c + 1);
	return c;
}

Band operator++(Band& b, int) // postfix operator
{
	Band result = b;
	++b;
	return result;
}

// Special behavior for --Band
Band operator--(Band &c) {
	
	//don't go lower than 160m
	if (c == Band::b160m)
	{
		return c;
	}
	
	c = static_cast<Band>(c - 1);
	return c;
}

Band operator--(Band& b, int) // postfix operator
{
	Band result = b;
	--b;
	return result;
}

void State::transmit()
{
	if (stateData.status == STATE_STANDBY)
	{
		return;
	}
	gpio_set_level(PTT_OUTPUT, 1);
	gpio_set_level(BIAS_DISABLE, 0);
	setStatus(STATE_TRANSMITTING);
	xTaskNotifyGive(displayHandle);
}

void State::receive()
{
	gpio_set_level(BIAS_DISABLE, 1);
	gpio_set_level(PTT_OUTPUT, 0);
	setStatus(STATE_RECEIVING);
	xTaskNotifyGive(displayHandle);
	
	//todo
	//save to nvs which band was used if it differs from what was previously saved. Maybe fork this off into a blocked task
	//this is a good time to save it because now everything is all in a safe stable state and we can take the time
}

void State::toggleStandby(void* param)
{
	ets_printf("Toggle standby\n");
	if (disableInterrupts)
	{
		return;
	}
	if (stateData.status == STATE_STANDBY)
	{
		receive();
	}
	else
	{
		//turn off the amp output in case it's in a transmitting or unknown state
		receive();
		setStatus(STATE_STANDBY);
		//todo: if it's being set to standby turn off the HV and 12v relay going to the T/R switch and LPF
	}
}

StateData State::getFullState() {
	return stateData;
}

Band State::setBandUp()
{
	if(stateData.status == STATE_TRANSMITTING)
	{
		return stateData.band;
	}
	
	stateData.band++;
	xTaskNotifyGive(displayHandle);
	return stateData.band;
}

Band State::setBandDown()
{
	if (stateData.status == STATE_TRANSMITTING)
	{
		return stateData.band;
	}
	
	stateData.band--;
	xTaskNotifyGive(displayHandle);
	return stateData.band;
}

void State::setup(TaskHandle_t  dH, TaskHandle_t  vH, TaskHandle_t  sMH, TaskHandle_t tmH)
{
	displayHandle = dH;
	voltageInputHandle = vH;
	safetyMonitorHandle = sMH;
	tempMonitorHandle = tmH;
	
	gpio_set_direction(PTT_INPUT, GPIO_MODE_INPUT);
	gpio_set_pull_mode(PTT_INPUT, GPIO_PULLUP_ONLY);
	gpio_set_direction(PTT_OUTPUT, GPIO_MODE_OUTPUT);
	gpio_set_level(PTT_OUTPUT, 0);
	gpio_set_direction(BIAS_DISABLE, GPIO_MODE_OUTPUT);
	gpio_set_level(PTT_OUTPUT, 1);
	

	gpio_set_intr_type(BUTTON_STANDBY, GPIO_INTR_NEGEDGE);
	gpio_set_direction(BUTTON_STANDBY, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON_STANDBY, GPIO_PULLUP_ONLY);
	
	
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

void State::startButtonISR()
{
	ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_STANDBY, State::toggleStandby, NULL));
}