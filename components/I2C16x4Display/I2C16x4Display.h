#ifndef DISPLAY_H
#define DISPLAY_H

#include "state.h"
#include <hd44780.h>
#include <pcf8574.h>
#include <sys/time.h>
#include <stdio.h>
#include <cstring>

#if defined(CONFIG_IDF_TARGET_ESP8266)
#define SDA_GPIO GPIO_NUM_4
#define SCL_GPIO GPIO_NUM_5
#else
#define SDA_GPIO GPIO_NUM_16
#define SCL_GPIO GPIO_NUM_17
#endif
#define I2C_ADDR 0x27

static const uint8_t char_data[] = {
      0x04, 0x0e, 0x0e, 0x0e, 0x1f, 0x00, 0x04, 0x00,
      0x1f, 0x11, 0x0a, 0x04, 0x0a, 0x11, 0x1f, 0x00
    };

class I2C16x4Display {
  public:
    void startDisplay();
    I2C16x4Display();
    static void startTask(void * pvParameters);
  protected:
    static esp_err_t write_lcd_data(const hd44780_t *lcd, uint8_t data);
    static uint32_t get_time_sec();
};

#endif
