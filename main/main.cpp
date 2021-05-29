#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

//#include <i2cdev.h>
#include "sdkconfig.h"
#include "StateController.h"
#include "lpf.h"
#include "I2C20x4Display.h"
#include "pins.h"

TaskHandle_t controllerHandle = NULL, displayHandle = NULL, lpfHandle = NULL;

extern "C" void app_main(void)
{

    printf("Starting LPF\n");
    //LPF lpf(LPF_3,LPF_2,LPF_1);


    StateController::setup();
    printf("Starting main state control\n");
    xTaskCreate(StateController::startSafetyMonitor, "StateController", configMINIMAL_STACK_SIZE * 10, NULL, 5, &controllerHandle);


    printf("Starting display\n");
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreate(I2C20x4Display::startDisplay, "Display", configMINIMAL_STACK_SIZE * 10, NULL, 5, &displayHandle);
    printf("TESTING4\n");

    vTaskStartScheduler();
}