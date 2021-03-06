#ifndef PINS_H
#define PINS_H

#include <driver/gpio.h>

#define LPF_1 GPIO_NUM_19
#define LPF_2 GPIO_NUM_18
#define LPF_3 GPIO_NUM_5

#define PTT_INPUT GPIO_NUM_34
#define PTT_OUTPUT GPIO_NUM_35

#define RF_VOLTS_FWD GPIO_NUM_32
#define RF_VOLTS_RVS GPIO_NUM_33

#define BIAS_DISABLE GPIO_NUM_23

#define LCD_SDA GPIO_NUM_16
#define LCD_SCL GPIO_NUM_17

//voltage 12v is i2c
//voltage 50v is i2c
//current 12v is i2c
//current 50v is i2c
//temp is i2c

#endif