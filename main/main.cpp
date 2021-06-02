#include "main.hpp"

#include <iostream>

// TaskHandle_t controllerHandle = NULL, displayHandle = NULL, lpfHandle = NULL;

extern "C" void app_main(void)
{
	//RunUnitTestsSelectedInIDE();
    printf("Starting LPF\n");
	//LPF lpf(LPF_3,LPF_2,LPF_1);
	
	printf("Starting display\n");
	auto displayHandle = Display::getTaskHandle();
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreate(Display::startDisplay, "Display", 4024, NULL, 5, &displayHandle);
	
	State::setup(displayHandle);
	SafetyMonitor::setup(displayHandle);
	
	auto safetyMonitorHandle = SafetyMonitor::getTaskHandle();
	printf("Starting main state control\n");
	xTaskCreate(SafetyMonitor::startSafetyMonitor, "StateController", 4024, NULL, 5, &safetyMonitorHandle);

	auto voltageInputHandle = Voltage::getTaskHandle();
	printf("Starting voltage monitor\n");
	xTaskCreate(Voltage::startVoltageInput, "VoltageInput", 1024, NULL, 5, &voltageInputHandle);

    printf("TESTING4\n");
//    vTaskDelete(NULL);
    //vTaskStartScheduler();
}