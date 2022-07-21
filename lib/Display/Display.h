#ifndef DISPLAY_H
#define DISPLAY_H

#include "pins.h"
#include "StateController.h"
#include <hd44780.h>
#include <pcf8574.h>
#include <sys/time.h>
#include <stdio.h>
#include <cstring>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cmath>
using namespace std; 


#if defined(CONFIG_IDF_TARGET_ESP8266)
#define SDA_GPIO GPIO_NUM_4
#define SCL_GPIO GPIO_NUM_5
#else
#define SDA_GPIO LCD_SDA
#define SCL_GPIO LCD_SCL
#endif
#define I2C_ADDR 0x27

#define BACKGROUND_BAND_SYMBOL 0
#define BACKGROUND_WATT_SYMBOL 1
#define BACKGROUND_SWR_SYMBOL 2
#define BACKGROUND_AMP_SYMBOL 3
#define BACKGROUND_VOLT_SYMBOL 4
#define BACKGROUND_TEMP_SYMBOL 5

struct textLocator {
  int col;
  int row;
  std::string text;
};

static TaskHandle_t displayHandle = NULL;;

static std::map<int, textLocator>background {
    {BACKGROUND_BAND_SYMBOL,textLocator{4,0, "m"}},
    {BACKGROUND_WATT_SYMBOL,textLocator{6,1, "W"}},
    {BACKGROUND_SWR_SYMBOL,textLocator{12,1, "SWR"}},
    {BACKGROUND_AMP_SYMBOL,textLocator{6,2, "A"}},
    {BACKGROUND_VOLT_SYMBOL,textLocator{19,2, "V"}},
    {BACKGROUND_TEMP_SYMBOL,textLocator{19,3, "C"}}
};

class Display {
  public:
    Display();
    static void startDisplay(void * state);
    static const constexpr int STATUS_INDEX = 0;
    static const constexpr int MODE_INDEX = 1;
  protected:
    static esp_err_t write_lcd_data(const hd44780* lcd,uint8_t data);
    hd44780_t lcd;
  private:
    void writeDynamicOutput();
    std::string rightAlignWidth(int columns, string input);
    double roundUp(double value, int decimal_places);
};

#endif
