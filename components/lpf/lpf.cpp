#include "lpf.h"
#include "driver/gpio.h"

LPF::LPF(int pin1, int pin2, int pin3) {
    this->lpfPins[0] = pin1;
    this->lpfPins[1] = pin2;
    this->lpfPins[2] = pin3;

    unsigned char outputPins = pin1 | pin2 | pin3;

    gpio_config_t ioconf;
    ioconf.mode = GPIO_MODE_OUTPUT;
    ioconf.pin_bit_mask = outputPins;
    gpio_config(&ioconf);

}