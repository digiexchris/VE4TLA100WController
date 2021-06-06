#include "SafetyMonitor.hpp"
#include "messages.hpp"

const double SafetyMonitor::VOLTAGE_MAX = 52.00;

volatile bool disableInterrupts = false;

void SafetyMonitor::startSafetyMonitor(void* param) {
	
	//block it until main tells it to start
	ulTaskNotifyTake( 
	pdTRUE,          /* Clear the notification value 
						before exiting. */
			portMAX_DELAY); /* Block indefinitely. */
	
	StateData stateData;
	
	vTaskDelay(50 / portTICK_PERIOD_MS);
	
	bool error = false;

	while(1) {
		
		xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
						ULONG_MAX, /* Reset the notification value to 0 on exit. */
						NULL, /* Notified value pass out in
												ulNotifiedValue. */
						pdMS_TO_TICKS(100));  /* Block for 100 MS and just continue otherwise incase a notification got missed*/

		stateData = State::getFullState();
		
		if (stateData.temp < -8)
		{
			error = true;
			State::setMode(MODE_ERROR);
			State::setStatus(STATE_ERROR_TEMP_SENSOR);
		}
		
		if(stateData.voltage > VOLTAGE_MAX) {
			//TODO: turn off the high voltage relay
			error = true;
			State::setMode(MODE_ERROR);
			State::setStatus(STATE_ERROR_VOLTS_HIGH);
		} 

		if(stateData.temp > 50.00) {
			error = true;
			State::setMode(MODE_ERROR);
			State::setStatus(STATE_ERROR_TEMP_HIGH);
		}

		if(stateData.current > 5) {
			error = true;
			State::setMode(MODE_ERROR);
			State::setStatus(STATE_ERROR_CURRENT_HIGH);
		}

		if(error) {
			//turn the amp off
//			 gpio_set_level(PTT_OUTPUT,0);
//			 gpio_set_level(BIAS_DISABLE,1);

			//make sure interrupts or other tasks can't turn the amp back on
			disableInterrupts = true;

			//update the display with the error
			

			//wait half a sec for the display to update
			

			//kill all except the display
			
			//note: suspendall isn't working, perhaps turn off individual tasks instead.
			vTaskSuspend(State::getVoltageInputHandle());
			vTaskDelay(500 / portTICK_PERIOD_MS);
			vTaskSuspend(State::getDisplayHandle());
			vTaskSuspend(State::getTempMonitorHandle());
			vTaskSuspend(State::getSafetyMonitorHandle());
			
		}
	}
	vTaskDelete(NULL);
}
