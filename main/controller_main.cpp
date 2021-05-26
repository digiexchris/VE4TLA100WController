#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <i2cdev.h>
#include "sdkconfig.h"
#include "state.h"
#include "lpf.h"
#include "I2C20x4Display.h"

extern "C" void app_main(void)
{
    
    LPF lpf(GPIO_NUM_12,GPIO_NUM_14,GPIO_NUM_27);
    State state;
    I2C20x4Display::startDisplay(&state);
}