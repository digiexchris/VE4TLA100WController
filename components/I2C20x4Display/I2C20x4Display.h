#ifndef DISPLAY_H
#define DISPLAY_H

#include "state.h"
#include <hd44780.h>
#include <pcf8574.h>
#include <sys/time.h>
#include <stdio.h>
#include <cstring>
#include "state.h"
#include <map>
#include <string>

#if defined(CONFIG_IDF_TARGET_ESP8266)
#define SDA_GPIO GPIO_NUM_4
#define SCL_GPIO GPIO_NUM_5
#else
#define SDA_GPIO GPIO_NUM_16
#define SCL_GPIO GPIO_NUM_17
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


// static std::map<std::string, std::string> messages {
//     {State::STATE_ERROR_SWR, "!SWR High"},
//     {State::STATE_ERROR_LPF, "!LPF Error"},
//     // {State::STATE_ERROR_VOLTS_LOW, "!Low Voltage"},
//     // {State::STATE_ERROR_VOLTS_HIGH, "!High Voltage"},
//     // {State::STATE_ERROR_TEMP_HIGH, "!High Temp"},
//     {State::STATE_ERROR_TEMP_SENSOR, "!Temp Sensor"},
//     // {State::STATE_TRANSMITTING, "Transmitting"},
//     {State::STATE_RECEIVING, "Receiving"},
//     {State::STATE_STANDBY, "Standby"}
// };

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
    void startDisplay();
    I2C20x4Display();
    static void startTask(void * pvParameters);
  protected:
    static esp_err_t write_lcd_data(const hd44780* lcd,uint8_t data);
    hd44780_t lcd;
  private:
    void writeDynamicOutput();
};

#endif
