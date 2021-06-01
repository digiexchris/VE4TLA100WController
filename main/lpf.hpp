#include <map>
#include "State.hpp"
#include <driver/gpio.h>

class LPF
{
protected:
    gpio_config_t ioconf;
    gpio_num_t lpfPins[3];
    std::map<Band, std::array<bool, 3>> bandMap
    {
        {Band::b160m, {true, true, true}},
        {Band::b80m, {false, false, false}},
        {Band::b60m, {false, false, true}},
        {Band::b40m, {false, true, false}},
        {Band::b30m, {false, true, false}},
        {Band::b20m, {false, true, true}},
        {Band::b17m, {false, true, true}},
        {Band::b15m, {true, false, false}},
        {Band::b12m, {true, false, false}},
        {Band::b10m, {true, false, false}},
        {Band::b6m, {true, false, true}},
    };

public:
    LPF(gpio_num_t pin1, gpio_num_t pin2, gpio_num_t pin3);
    esp_err_t setBand(Band);
};