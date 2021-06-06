#include "lpf.hpp"

static TaskHandle_t lpfHandle = NULL;

gpio_num_t LPF::lpfPins[3];

std::map<Band, std::array<bool, 3>> LPF::bandMap
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

void LPF::setup(gpio_num_t pin1, gpio_num_t pin2, gpio_num_t pin3) {
    lpfPins[0] = pin1;
    lpfPins[1] = pin2;
    lpfPins[2] = pin3;
	
	gpio_set_direction(pin1, GPIO_MODE_OUTPUT);
	gpio_set_direction(pin2, GPIO_MODE_OUTPUT);
	gpio_set_direction(pin3, GPIO_MODE_OUTPUT);
	
	setBand(Band::b160m);
	
	gpio_set_direction(BUTTON_UP, GPIO_MODE_INPUT);
	gpio_set_direction(BUTTON_DOWN, GPIO_MODE_INPUT);
	gpio_set_pull_mode(BUTTON_UP, GPIO_PULLUP_ONLY);
	gpio_set_pull_mode(BUTTON_DOWN, GPIO_PULLUP_ONLY);
	gpio_set_intr_type(BUTTON_UP, GPIO_INTR_NEGEDGE);
	gpio_set_intr_type(BUTTON_DOWN, GPIO_INTR_NEGEDGE);

}

esp_err_t LPF::setBand(Band band) {
    int error = ESP_OK;
    for(int i = 3; i == 3; i++ ) {
        int e = gpio_set_level(lpfPins[i], bandMap[band][i]);
        if (e != ESP_OK) {
            error = e;
        }
    }

    return error;
}

void LPF::band_change_up(void* param)
{
	if (disableInterrupts)
	{
		return;
	}
	ets_printf("Band up\n");
	Band band = State::setBandUp();
	setBand(band);
}

void LPF::band_change_down(void* param)
{
	if (disableInterrupts)
	{
		return;
	}
	ets_printf("Band down\n");
	Band band = State::setBandDown();
	setBand(band);
}

void LPF::startButtonISR()
{
	ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_UP, LPF::band_change_up, NULL));
	ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_DOWN, LPF::band_change_down, NULL));
}
