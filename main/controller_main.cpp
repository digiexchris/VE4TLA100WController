#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <i2cdev.h>
#include "sdkconfig.h"
#include "state.h"
#include "lpf.h"
#include "I2C20x4Display.h"

extern "C" void app_main(void)
{
    State state;
    LPF lpf(GPIO_NUM_12,GPIO_NUM_14,GPIO_NUM_27);
    
    I2C20x4Display display;
    display.startDisplay();
}


