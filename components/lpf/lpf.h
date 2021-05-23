#include <map>
#include "state.h"
#include <driver/gpio.h>

class LPF
{
protected:
    gpio_config_t ioconf;
    gpio_num_t lpfPins[3];
    std::map<State::Band, std::array<bool, 3>> bandMap
    {
        {State::Band::b160m, {true, true, true}},
        {State::Band::b80m, {false, false, false}},
        {State::Band::b60m, {false, false, true}},
        {State::Band::b40m, {false, true, false}},
        {State::Band::b30m, {false, true, false}},
        {State::Band::b20m, {false, true, true}},
        {State::Band::b17m, {false, true, true}},
        {State::Band::b15m, {true, false, false}},
        {State::Band::b12m, {true, false, false}},
        {State::Band::b10m, {true, false, false}},
        {State::Band::b6m, {true, false, true}},
    };

public:
    LPF(gpio_num_t pin1, gpio_num_t pin2, gpio_num_t pin3);
    esp_err_t setBand(State::Band);
};