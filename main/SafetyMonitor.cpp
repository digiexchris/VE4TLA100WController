#include "SafetyMonitor.hpp"
#include "messages.hpp"

const double SafetyMonitor::VOLTAGE_MAX = 52.00;

volatile bool disableInterrupts = false;

TaskHandle_t SafetyMonitor::displayHandle = NULL;

void SafetyMonitor::setup(TaskHandle_t  dH)
{
	displayHandle = dH;
}

void SafetyMonitor::startSafetyMonitor(void* param) {
	
	StateData stateData;
	
	vTaskDelay(50 / portTICK_PERIOD_MS);

	while(1) {
		
//TODO notify this from any monitors
		xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
						ULONG_MAX, /* Reset the notification value to 0 on exit. */
						NULL, /* Notified value pass out in
												ulNotifiedValue. */
						pdMS_TO_TICKS(100));  /* Block for 100 MS and just continue otherwise incase a notification got missed*/

		stateData = State::getFullState();
		
		if(stateData.voltage > VOLTAGE_MAX) {
			stateData.status = STATE_ERROR_VOLTS_HIGH;
			stateData.mode = MODE_ERROR;
		} 

		if(stateData.temp > 50.00) {
			stateData.status = STATE_ERROR_TEMP_HIGH;
			stateData.mode = MODE_ERROR;
		}

		if(stateData.current > 5) {
			stateData.status = STATE_ERROR_CURRENT_HIGH;
			stateData.mode = MODE_ERROR;
		}

		if(stateData.mode == MODE_ERROR) {
			//turn the amp off
//			 gpio_set_level(PTT_OUTPUT,0);
//			 gpio_set_level(BIAS_DISABLE,1);

			//make sure interrupts or other tasks can't turn the amp back on
			disableInterrupts = true;

			//update the display with the error
			

			//wait half a sec for the display to update
			

			//kill all except the display
			
			//note: suspendall isn't working, perhaps turn off individual tasks instead.
			vTaskSuspendAll();
		
			vTaskResume(displayHandle);
			vTaskDelay(500 / portTICK_PERIOD_MS);
			xTaskNotifyGive( displayHandle);
		}
	}
	vTaskDelete(NULL);
}
