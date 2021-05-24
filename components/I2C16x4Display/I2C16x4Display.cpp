#include "I2C16x4Display.h"

static i2c_dev_t pcf8574;

I2C16x4Display::I2C16x4Display() {
    
}

uint32_t I2C16x4Display::get_time_sec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}

esp_err_t I2C16x4Display::write_lcd_data(const hd44780_t *lcd, uint8_t data)
{
    return pcf8574_port_write(&pcf8574, data);
}

void I2C16x4Display::startTask(void * pvParameters)
{
    hd44780_t lcd = {
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

    ESP_ERROR_CHECK(hd44780_init(&lcd));

    hd44780_switch_backlight(&lcd, true);

    hd44780_upload_character(&lcd, 0, char_data);
    hd44780_upload_character(&lcd, 1, char_data + 8);

    hd44780_gotoxy(&lcd, 0, 0);
    hd44780_puts(&lcd, "\x08 Hello world!");
    hd44780_gotoxy(&lcd, 0, 1);
    hd44780_puts(&lcd, "\x09 ");

    char time[16];

    while (1)
    {
        hd44780_gotoxy(&lcd, 2, 1);

        snprintf(time, 7, "%u  ", get_time_sec());
        time[sizeof(time) - 1] = 0;

        hd44780_puts(&lcd, time);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void I2C16x4Display::startDisplay() {
    static uint8_t ucParameterToPass;
    TaskHandle_t xHandle = NULL;
    ESP_ERROR_CHECK(i2cdev_init());
    xTaskCreate(startTask, "lcd_test", configMINIMAL_STACK_SIZE * 5, &ucParameterToPass, 5, &xHandle);
}