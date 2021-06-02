#include "Voltage.hpp"
#include <iostream>
void Voltage::startVoltageInput(void* param) {
	
	//block it until main tells it to start
	ulTaskNotifyTake( 
	pdTRUE,          /* Clear the notification value 
						before exiting. */
			portMAX_DELAY); /* Block indefinitely. */
	
	double voltage = 51.00;
	
	while(1) {
		
		cout << "Voltage bump" << endl;
		//simulating stuff happening
		voltage = voltage + 0.1;

		//double v = gpio_read(voltage_pin) or whatever

		State ::setVoltage(voltage);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}