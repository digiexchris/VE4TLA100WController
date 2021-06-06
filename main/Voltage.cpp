#include "Voltage.hpp"
#include <iostream>
void Voltage::startVoltageInput(void* param) {
	
	//block it until main tells it to start
	ulTaskNotifyTake( 
	pdTRUE,          /* Clear the notification value 
						before exiting. */
			portMAX_DELAY); /* Block indefinitely. */
	
	double voltage = 50.00;
	
	while(1) {
		
		//simulating stuff happening
		voltage = voltage;

		//double v = gpio_read(voltage_pin) or whatever

		State ::setVoltage(voltage);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}