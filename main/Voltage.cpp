#include "Voltage.hpp"
#include <iostream>
void Voltage::startVoltageInput(void* param) {

	vTaskDelay(50 / portTICK_PERIOD_MS);
	
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