#include "SafetyMonitor.hpp"
#include "messages.hpp"

const double SafetyMonitor::VOLTAGE_MAX = 52.00;

volatile bool disableInterrupts = false;


void SafetyMonitor::startSafetyMonitor(void* param) {
	
	StateData stateData;
	
	vTaskDelay(50 / portTICK_PERIOD_MS);

	while(1) {
		

		xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
						ULONG_MAX, /* Reset the notification value to 0 on exit. */
						NULL, /* Notified value pass out in
												ulNotifiedValue. */
						pdMS_TO_TICKS(100));  /* Block for 100 MS and just continue otherwise incase a notification got missed*/

		StateData stateData = State::getFullState();
		
		if(stateData.voltage > VOLTAGE_MAX) {
			stateData.status = STATE_ERROR_VOLTS_HIGH;
			stateData.mode = MODE_ERROR;
			xTaskNotifyGive( displayHandle);
		} 

		if(stateData.temp > 50.00) {
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
	vTaskDelete(NULL);
}

//void State::startVoltageInput(void* param) {
//
//	vTaskDelay(50 / portTICK_PERIOD_MS);
//
//	while(1) {
//
//		//double v = gpio_read(voltage_pin) or whatever
//
//		stateData.voltage = stateData.voltage + 0.01;
//
//		//tell the display to update the voltage
//		xTaskNotifyGive( displayHandle);
//
//		vTaskDelay(100 / portTICK_PERIOD_MS);
//	}
//
//	vTaskDelete(NULL);
//}
