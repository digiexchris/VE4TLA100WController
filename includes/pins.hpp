#ifndef PINS_H
#define PINS_H

#include <driver/gpio.h>
#include <ds18x20.h>

//TODO HOOK UP LPF SOFTWARE
#define LPF_1 GPIO_NUM_19
#define LPF_2 GPIO_NUM_18
#define LPF_3 GPIO_NUM_5


//TODO HOOK UP BUTTON SOFTWARE
#define BUTTON_RESET GPIO_NUM_13 // touch 4
#define BUTTON_STANDBY GPIO_NUM_32 // touch 9
#define BUTTON_UP GPIO_NUM_33 // touch 8
#define BUTTON_DOWN GPIO_NUM_2 // touch 2

#define TEMP_SENSOR_PIN GPIO_NUM_4

//TODO HOOK UP PTT AND BIAS FUNCTIONALITY
#define PTT_INPUT GPIO_NUM_34
#define PTT_OUTPUT GPIO_NUM_25
#define BIAS_DISABLE GPIO_NUM_23

//TODO HOOK UP POWER AND SWR FUNCTIONALITY
#define FWD_VOLTS GPIO_NUM_36
#define RFL_VOLTS GPIO_NUM_39

#define LCD_SDA GPIO_NUM_16
#define LCD_SCL GPIO_NUM_17

//TODO BEEP ON BUTTON PRESS
#define UI_BEEPER GPIO_NUM_22


//26, 27, 14, 12, 15 reserved for JTAG

//voltage 12v is i2c
//voltage 50v is i2c
//current 12v is i2c
//current 50v is i2c
//temp is i2c

//IO0 is boot/flash


/* remaining pins
 * IO35
 * SD2
 * SD3
 * CMD
 * 
 *
 *TXD0
 *RXD0
 *IO21
 *SD0
 *SD1
 *CLK
 */

#endif