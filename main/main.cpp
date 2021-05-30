#include "main.h"

#include <iostream>

// TaskHandle_t controllerHandle = NULL, displayHandle = NULL, lpfHandle = NULL;

extern "C" void app_main(void)
{

    printf("Starting LPF\n");
    //LPF lpf(LPF_3,LPF_2,LPF_1);


    StateController::setup();
    printf("Starting main state control\n");
    auto err = xTaskCreate(StateController::startSafetyMonitor, "StateController", 4024, NULL, 5, &stateControllerHandle);

    printf("Starting display\n");
    ESP_ERROR_CHECK(i2cdev_init());
    auto err2 = xTaskCreate(I2C20x4Display::startDisplay, "Display", 4024, NULL, 5, &displayHandle);
    printf("TESTING4\n");
    vTaskDelete(NULL);

    // while(1) {

    //     std::cout << "TESTING" << std::endl;
    //     vTaskDelay(500 / portTICK_PERIOD_MS);
    // }
    //vTaskStartScheduler();
}