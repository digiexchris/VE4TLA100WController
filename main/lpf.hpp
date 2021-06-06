#include <map>
#include "State.hpp"
#include <driver/gpio.h>

#define ESP_INTR_FLAG_DEFAULT 0

#define GPIO_BUTTON_INPUT_PIN_SEL  ((1ULL<<BUTTON_UP) | (1ULL<<BUTTON_DOWN))

class LPF
{
protected:
    gpio_config_t ioconf;
    static gpio_num_t lpfPins[3];
	static std::map<Band, std::array<bool, 3>> bandMap;

public:
    static void setup(gpio_num_t pin1, gpio_num_t pin2, gpio_num_t pin3);
	static void IRAM_ATTR band_change_up(void* param);
	static void IRAM_ATTR band_change_down(void* param);
	static void startButtonISR();
    static esp_err_t setBand(Band);
};