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
    xTaskCreate(Display::startDisplay, "Display", 4024, NULL, 5, displayHandle);

	auto safetyMonitorHandle = SafetyMonitor::getTaskHandle();
    printf("Starting main state control\n");
	xTaskCreate(SafetyMonitor::startSafetyMonitor, "StateController", 4024, NULL, 5, safetyMonitorHandle);

    
//	printf("Starting voltage monitor\n");
//	xTaskCreate(StateController::startVoltageInput, "VoltageInput", 2024, NULL, 5, NULL);

    printf("TESTING4\n");
    vTaskDelete(NULL);

    // while(1) {

    //     std::cout << "TESTING" << std::endl;
    //     vTaskDelay(500 / portTICK_PERIOD_MS);
    // }
    //vTaskStartScheduler();
}