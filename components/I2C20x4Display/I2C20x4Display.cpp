#include "I2C20x4Display.h"

static i2c_dev_t pcf8574;

I2C20x4Display::I2C20x4Display() {
    
}

esp_err_t I2C20x4Display::write_lcd_data(const hd44780* lcd, uint8_t data)
{
    return pcf8574_port_write(&pcf8574, data);
}

void I2C20x4Display::startTask(void * pvParameters)
{

    //Initialize the display
    I2C20x4Display display;

    display.lcd = hd44780_t{
        .write_cb = write_lcd_data, // use callback to send data to LCD by I2C GPIO expander
        .pins = {
            .rs = 0,
            .e  = 2,
            .d4 = 4,
            .d5 = 5,
            .d6 = 6,
            .d7 = 7,
            .bl = 3
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

    //Start the loop of updating the display
    display.writeDynamicOutput();
}

void I2C20x4Display::writeDynamicOutput() {

    while (1) {

        //TODO: get stateData from State and format it to the correct 
        //decimals and spacing

        std::map<std::string,textLocator> stateData {
            {"BAND",textLocator{3,0," 80"}},
            {"FREQUENCY",textLocator{14,0,"Manual"}},
            {"POWER",textLocator{0,1,"100.00"}},
            {"SWR",textLocator{16,1,"1.99"}},
            {"CURRENT",textLocator{1,2,"20.55"}},
            {"VOLTAGE",textLocator{14,2,"50.77"}},
            {"STATUS",textLocator{0,3,"Receiving"}},
            {"TEMP",textLocator{14,3,"32.18"}}
        };

        std::map<std::string, textLocator>::iterator it = stateData.begin();

        while (it != stateData.end()) {
            textLocator tl = it->second; //second thing is the value, first thing is the key

            hd44780_gotoxy(&lcd, tl.col, tl.row);
            hd44780_puts(&lcd,tl.text.c_str());
            it++;
        }
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void I2C20x4Display::startDisplay() {
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreate(startTask, "lcd_test", configMINIMAL_STACK_SIZE * 5, &ucParameterToPass, 5, &xHandle);
}