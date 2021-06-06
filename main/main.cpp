#include "main.hpp"

#include <iostream>

// TaskHandle_t controllerHandle = NULL, displayHandle = NULL, lpfHandle = NULL;

extern "C" void app_main(void)
{
	//RunUnitTestsSelectedInIDE();
    printf("Starting LPF\n");
	LPF::setup(LPF_3,LPF_2,LPF_1);
	printf("Starting display\n");
	auto displayHandle = Display::getTaskHandle();
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreate(Display::startDisplay, "Display", 4024, NULL, 5, &displayHandle);
	
	printf("Starting temp monitor\n");
	auto tempMonitorHandle = TempMonitor::getTaskHandle();
	xTaskCreate(TempMonitor::startTempMonitor, "TempMonitor", 1024, NULL, 5, &tempMonitorHandle);
	
	auto safetyMonitorHandle = SafetyMonitor::getTaskHandle();
	printf("Starting main state control\n");
	xTaskCreate(SafetyMonitor::startSafetyMonitor, "StateController", 4024, NULL, 10, &safetyMonitorHandle);

	auto voltageInputHandle = Voltage::getTaskHandle();
	printf("Starting voltage monitor\n");
	xTaskCreate(Voltage::startVoltageInput, "VoltageInput", 1024, NULL, 5, &voltageInputHandle);
	
	State::setup(displayHandle, voltageInputHandle, safetyMonitorHandle, tempMonitorHandle);
	
	//tell them they can start
	xTaskNotifyGive(displayHandle);
	xTaskNotifyGive(voltageInputHandle);
	xTaskNotifyGive(safetyMonitorHandle);
	xTaskNotifyGive(tempMonitorHandle);
	
	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
	LPF::startButtonISR();
	State::startButtonISR();
	
    printf("Done startup\n");
//    vTaskDelete(NULL);
    //vTaskStartScheduler();
}