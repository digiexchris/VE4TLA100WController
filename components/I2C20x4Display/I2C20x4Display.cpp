#include "I2C20x4Display.h"

using namespace std;

static i2c_dev_t pcf8574;

I2C20x4Display::I2C20x4Display() {
    
}

esp_err_t I2C20x4Display::write_lcd_data(const hd44780* lcd, uint8_t data)
{
    return pcf8574_port_write(&pcf8574, data);
}

void I2C20x4Display::startDisplay(State* state) {

    printf("GotFulLState()\n");
    TaskHandle_t xHandle = NULL;
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreate(startTask, "lcd_test", configMINIMAL_STACK_SIZE * 10, &state, 5, &xHandle);
}

void I2C20x4Display::startTask(void * state)
{
    //Initialize the display
    I2C20x4Display display;

    display.lcd = hd44780_t{
        .write_cb = write_lcd_data, // use callback to send data to LCD by I2C GPIO expander
        .pins = {
            0,
            2,
            4,
            5,
            6,
            7,
            3
        },
        .font = HD44780_FONT_5X8,
        .lines = 4,
        true
    };

    memset(&pcf8574, 0, sizeof(i2c_dev_t));
    ESP_ERROR_CHECK(pcf8574_init_desc(&pcf8574, 0, I2C_ADDR, SDA_GPIO, SCL_GPIO));

    ESP_ERROR_CHECK(hd44780_init(&display.lcd));

    hd44780_switch_backlight(&display.lcd, true);

    //Write out the static background
    std::map<int, textLocator>::iterator it = background.begin();

    while (it != background.end()) {

        textLocator tl = it->second; //second thing is the value, first thing is the key

        hd44780_gotoxy(&display.lcd, tl.col, tl.row);
        hd44780_puts(&display.lcd,tl.text.c_str());

        it++;
    }

    // Start the loop of updating the display
    display.writeDynamicOutput((State*)state);
}
#include <iostream>
void I2C20x4Display::writeDynamicOutput(State* state) {
    while (1) {

        auto fullState = state->getFullState();

        // cout << "band" << fullState.band << endl;
        // cout << fullState.mode << endl;
        // cout << fullState.power << endl;
        // cout << fullState.swr << endl;
        // cout << fullState.current << endl;
        // cout << fullState.voltage << endl;
        // cout << fullState.temp << endl;
        // cout << fullState.status << endl;


        // std::ostringstream band, mode, power, swr, current, voltage, temp;

        // band << std::setw(3) << fullState.band;
        // mode << std::setw(6) << fullState.mode;
        // power << std::setw(5) << std::fixed << std::setprecision(2) << fullState.power;
        // swr << std::setw(4) << std::fixed << std::setprecision(2) << fullState.swr;
        // current << std::setw(5) << std::fixed << std::setprecision(2) << fullState.current;
        // voltage << std::setw(4) << std::fixed << std::setprecision(2) << fullState.voltage;
        // temp << std::setw(4) << std::fixed << std::setprecision(2) << fullState.temp;
        

        // std::map<std::string,textLocator> stateData {
        //     {"BAND",textLocator{3,0,band.str()}},
        //     {"FREQUENCY",textLocator{14,0,mode.str()}},
        //     {"POWER",textLocator{0,1,power.str()}},
        //     {"SWR",textLocator{16,1,swr.str()}},
        //     {"CURRENT",textLocator{1,2,current.str()}},
        //     {"VOLTAGE",textLocator{14,2,voltage.str()}},
        //     {"STATUS",textLocator{0,3,messages[fullState.status]}},
        //     {"TEMP",textLocator{14,3,temp.str()}}
        // };

        // std::map<std::string, textLocator>::iterator it = stateData.begin();

        // while (it != stateData.end()) {
        //     textLocator tl = it->second; //second thing is the value, first thing is the key

        //     hd44780_gotoxy(&lcd, tl.col, tl.row);
        //     hd44780_puts(&lcd,tl.text.c_str());
        //     it++;
        // }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
