#include "StateController.h"

const char* StateController::STATE_ERROR_SWR = "ERROR_SWR";
const char* StateController::STATE_ERROR_LPF = "ERROR_LPF";
const char* StateController::STATE_ERROR_VOLTS_LOW = "ERROR_VOLTS_LOW";
const char* StateController::STATE_ERROR_VOLTS_HIGH = "ERROR_VOLTS_HIGH";
const char* StateController::STATE_ERROR_TEMP_HIGH = "ERROR_TEMP_HIGH";
const char* StateController::STATE_ERROR_TEMP_SENSOR = "ERROR_TEMP_SENSOR";
const char* StateController::STATE_ERROR_CURRENT_HIGH = "ERROR_CURRENT_HIGH";
const char* StateController::STATE_TRANSMITTING = "TRANSMITTING";
const char* StateController::STATE_RECEIVING = "RECEIVING";
const char* StateController::STATE_STANDBY = "STANDBY";
const char* StateController::MODE_MANUAL = "MANUAL";
const char* StateController::MODE_AUTOMATIC = "AUTOMATIC";
const char* StateController::MODE_ERROR = "ERROR";

const double StateController::VOLTAGE_MAX = 52.00;

volatile bool disableInterrupts = false;

void StateController::setup() {
	StateController::stateData = {
		.voltage = 21.33,
		.current = 19.33,
		.power = 100.33,
		.swr = 1.9944,
		.temp = 32.11,
		.band = Band::b160m,
		.status = STATE_ERROR_SWR,
		.mode = MODE_AUTOMATIC
	};
}

void StateController::startSafetyMonitor(void* param) {
	vTaskDelay(50 / portTICK_PERIOD_MS);
	auto displayHandle = pcTaskGetTaskName("Display");

	while(1) {

		xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
						ULONG_MAX, /* Reset the notification value to 0 on exit. */
						NULL, /* Notified value pass out in
												ulNotifiedValue. */
						pdMS_TO_TICKS(100));  /* Block for 100 MS and just continue otherwise incase a notification got missed*/

		if(stateData.voltage > 52) {
			stateData.status = STATE_ERROR_VOLTS_HIGH;
			stateData.mode = MODE_ERROR;
			xTaskNotifyGive( displayHandle);
		} 

		if(stateData.temp > 26.00) {
			stateData.status = STATE_ERROR_TEMP_HIGH;
			stateData.mode = MODE_ERROR;
			xTaskNotifyGive( displayHandle);
		}

		if(stateData.current > 5) {
			stateData.status = STATE_ERROR_CURRENT_HIGH;
			stateData.mode = MODE_ERROR;
		}

		if(stateData.mode == MODE_ERROR) {
			//turn the amp off
			gpio_set_level(PTT_OUTPUT,0);
			gpio_set_level(BIAS_DISABLE,1);

			//make sure interrupts or other tasks can't turn the amp back on
			disableInterrupts = true;

			//update the display with the error
			xTaskNotifyGive( displayHandle);

			//wait half a sec for the display to update
			vTaskDelay(500 / portTICK_PERIOD_MS);

			//kill it
			vTaskSuspendAll();
		}
	}
}

void StateController::startVoltageMonitor(void* param) {

	vTaskDelay(50 / portTICK_PERIOD_MS);
	auto displayHandle = xTaskGetHandle("Display");

	while(1) {

		//double v = gpio_read(voltage_pin) or whatever
		double v = 50.11;
		if (v > VOLTAGE_MAX)
		stateData.voltage = stateData.voltage + 0.01;

		//tell the display to update the voltage
		xTaskNotifyGive( displayHandle);

		//temporary. Let it run as fast as possible once it has something to do
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

StateData StateController::getFullState() {
	return stateData;
}
