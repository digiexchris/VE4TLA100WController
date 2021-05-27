#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <i2cdev.h>
#include "sdkconfig.h"
#include "state.h"
#include "lpf.h"
#include "I2C20x4Display.h"
#include <iostream>

extern "C" void app_main(void)
{
    printf("TESTING1\n");
    //LPF lpf(GPIO_NUM_12,GPIO_NUM_14,GPIO_NUM_27);
    printf("TESTING2\n");
    State state;
    printf("TESTING3\n");
    I2C20x4Display::startDisplay(&state);
    printf("TESTING4\n");
    std::cout << "test";
}