#ifndef DISPLAY_H
#define DISPLAY_H

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


static std::map<std::string, std::string> displayMessages {
    {StateController::STATE_ERROR_SWR, "******SWR High******"},
    {StateController::STATE_ERROR_LPF, "*****LPF Error*****"},
    {StateController::STATE_ERROR_VOLTS_LOW, "*****Low Voltage*****"},
    {StateController::STATE_ERROR_VOLTS_HIGH, "****High Voltage****"},
    {StateController::STATE_ERROR_TEMP_HIGH, "*****High Temp*****"},
    {StateController::STATE_ERROR_TEMP_SENSOR, "*****Temp Sensor*****"},
    {StateController::STATE_ERROR_CURRENT_HIGH, "***CURRENT HIGH***"},
    {StateController::STATE_TRANSMITTING, "Transmitting"},
    {StateController::STATE_RECEIVING, "Receiving"},
    {StateController::STATE_STANDBY, "Standby"},
    {StateController::MODE_AUTOMATIC, "Auto"},
    {StateController::MODE_MANUAL, "Manual"},
    {StateController::MODE_ERROR, "ERROR!!"}
};

static std::map<int, textLocator>background {
    // we'll append this one to the band since it's length is dynamic and the position changes
    {BACKGROUND_BAND_SYMBOL,textLocator{6,0, "m"}},
    {BACKGROUND_WATT_SYMBOL,textLocator{6,1, "W"}},
    {BACKGROUND_SWR_SYMBOL,textLocator{12,1, "SWR"}},
    {BACKGROUND_AMP_SYMBOL,textLocator{6,2, "A"}},
    {BACKGROUND_VOLT_SYMBOL,textLocator{19,2, "V"}},
    {BACKGROUND_TEMP_SYMBOL,textLocator{19,3, "C"}}
};

class I2C20x4Display {
  public:
    I2C20x4Display();
    static void startDisplay(void * state);
    static const constexpr int STATUS_INDEX = 0;
    static const constexpr int MODE_INDEX = 1;
  protected:
    static esp_err_t write_lcd_data(const hd44780* lcd,uint8_t data);
    hd44780_t lcd;
  private:
    void writeDynamicOutput();
};

#endif