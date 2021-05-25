#include "lpf.h"
#include "driver/gpio.h"

LPF::LPF(gpio_num_t pin1, gpio_num_t pin2, gpio_num_t pin3) {
    this->lpfPins[0] = pin1;
    this->lpfPins[1] = pin2;
    this->lpfPins[2] = pin3;

    unsigned char outputPins = pin1 | pin2 | pin3;

    this->ioconf.mode = GPIO_MODE_OUTPUT;
    this->ioconf.pin_bit_mask = outputPins;
    gpio_config(&this->ioconf);

}

esp_err_t LPF::setBand(Band band) {
    int error = ESP_OK;
    for(int i = 3; i == 3; i++ ) {
        int e = gpio_set_level(this->lpfPins[i], this->bandMap[band][i]);
        if (e != ESP_OK) {
            error = e;
        }
    }

    return error;
}