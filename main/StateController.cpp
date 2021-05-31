#include "StateController.hpp"
#include "messages.hpp"

const double StateController::VOLTAGE_MAX = 52.00;

volatile bool disableInterrupts = false;

const string BandToString(Band v)
{
    switch (v)
    {
        case b160m:   return string("160");
        case b80m:   return string("80");
        case b60m: return string("60");
        case b40m: return string("40");
        case b30m: return string("30");
        case b20m: return string("20");
        case b17m: return string("17");
        case b15m: return string("15");
        case b12m: return string("12");
        case b10m: return string("10");
        case b6m: return string("6");
        default:      return string("??");
    }
}

StateData StateController::stateData = {
		.voltage = 21.33333,
		.current = 19.33443,
		.power = 100.3344343,
		.swr = 1.99443,
		.temp = 32.11343,
		.band = Band::b160m,
		.status = STATE_ERROR_SWR,
		.mode = MODE_AUTOMATIC
	};

void StateController::setup() {
	//set GPIO or something maybe
}

void StateController::startSafetyMonitor(void* param) {
	
	vTaskDelay(50 / portTICK_PERIOD_MS);

	while(1) {

		xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
						ULONG_MAX, /* Reset the notification value to 0 on exit. */
						NULL, /* Notified value pass out in
												ulNotifiedValue. */
						pdMS_TO_TICKS(100));  /* Block for 100 MS and just continue otherwise incase a notification got missed*/

		if(stateData.voltage > 52) {
			stateData.status = STATE_ERROR_VOLTS_HIGH;
			stateData.mode = MODE_ERROR;
			//xTaskNotifyGive( displayHandle);
		} 

		if(stateData.temp > 26.00) {
			stateData.status = STATE_ERROR_TEMP_HIGH;
			stateData.mode = MODE_ERROR;
			//xTaskNotifyGive( displayHandle);
		}

		if(stateData.current > 5) {
			stateData.status = STATE_ERROR_CURRENT_HIGH;
			stateData.mode = MODE_ERROR;
		}

		if(stateData.mode == MODE_ERROR) {
			//turn the amp off
			// gpio_set_level(PTT_OUTPUT,0);
			// gpio_set_level(BIAS_DISABLE,1);

			//make sure interrupts or other tasks can't turn the amp back on
			disableInterrupts = true;

			//update the display with the error
			//xTaskNotifyGive( displayHandle);

			//wait half a sec for the display to update
			vTaskDelay(500 / portTICK_PERIOD_MS);

			//kill it
			//vTaskSuspendAll();
		}
	}
	vTaskDelete(NULL);
}

void StateController::startVoltageMonitor(void* param) {

	vTaskDelay(50 / portTICK_PERIOD_MS);

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

	vTaskDelete(NULL);
}

StateData StateController::getFullState() {
	return stateData;
}
