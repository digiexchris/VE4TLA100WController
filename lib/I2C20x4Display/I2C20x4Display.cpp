#include "I2C20x4Display.h"
#include "messages.h"

static std::map<std::string, std::string> displayMessages {
    {STATE_ERROR_SWR, "******SWR High******"},
    {STATE_ERROR_LPF, "*****LPF Error*****"},
    {STATE_ERROR_VOLTS_LOW, "*****Low Voltage*****"},
    {STATE_ERROR_VOLTS_HIGH, "****High Voltage****"},
    {STATE_ERROR_TEMP_HIGH, "*****High Temp*****"},
    {STATE_ERROR_TEMP_SENSOR, "*****Temp Sensor*****"},
    {STATE_ERROR_CURRENT_HIGH, "***CURRENT HIGH***"},
    {STATE_TRANSMITTING, "Transmitting"},
    {STATE_RECEIVING, "Receiving"},
    {STATE_STANDBY, "Standby"},
    {MODE_AUTOMATIC, "Auto"},
    {MODE_MANUAL, "Manual"},
    {MODE_ERROR, "ERROR!!"}
};

using namespace std;

static i2c_dev_t pcf8574;

I2C20x4Display::I2C20x4Display() {
    
}

esp_err_t I2C20x4Display::write_lcd_data(const hd44780* lcd, uint8_t data)
{
    return pcf8574_port_write(&pcf8574, data);
}

#include <iostream>
void I2C20x4Display:: startDisplay(void * params)
{
    std::cout << "started Display" << std::endl;
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

    ESP_ERROR_CHECK(hd44780_switch_backlight(&display.lcd, true));

    //Write out the static background
    std::map<int, textLocator>::iterator it = background.begin();

    while (it != background.end()) {

        textLocator tl = it->second; //second thing is the value, first thing is the key

        hd44780_gotoxy(&display.lcd, tl.col, tl.row);
        hd44780_puts(&display.lcd,tl.text.c_str());

        it++;
    }

    // Start the loop of updating the display
    display.writeDynamicOutput();

    vTaskDelete(NULL);
}

void I2C20x4Display::writeDynamicOutput() {
    
    std::string band, mode, power, swr, current, voltage, temp, status;
    
    while (1) {

        vTaskDelay(500/portTICK_PERIOD_MS);
        //block to wait for a notification that it should update
        // xTaskNotifyWait( 0x00,      /* Don't clear any notification bits on entry. */
        //                     ULONG_MAX, /* Reset the notification value to 0 on exit. */
        //                     NULL, /* Notified value pass out in
        //                                             ulNotifiedValue. */
        //                     portMAX_DELAY );  /* Block forever until a notification comes in*/
        auto state = StateController::getFullState();

        band = BandToString(state.band);
        
        band = rightAlignWidth(4, band.substr(1));
        mode = rightAlignWidth(10,string(state.mode));
        power = rightAlignWidth(6,to_string(state.power));
        swr = rightAlignWidth(4,to_string(state.swr));
        current = rightAlignWidth(5,to_string(state.current));
        voltage = rightAlignWidth(5,to_string(state.voltage));
        temp = rightAlignWidth(2,to_string(state.temp));
        status = rightAlignWidth(12,string(state.status));

        std::string statusMsg = displayMessages[state.status];

        std::map<std::string,textLocator> stateData {
            {"BAND",textLocator{3,0,band}},
            {"FREQUENCY",textLocator{14,0,mode}},
            {"POWER",textLocator{0,1,power}},
            {"SWR",textLocator{16,1,swr}},
            {"CURRENT",textLocator{1,2,current}},
            {"VOLTAGE",textLocator{14,2,voltage}},
            {"STATUS",textLocator{0,3,statusMsg}},
            {"TEMP",textLocator{14,3,temp}}
        };

        std::map<std::string, textLocator>::iterator it = stateData.begin();

        while (it != stateData.end()) {
            textLocator tl = it->second; //second thing is the value, first thing is the key

            hd44780_gotoxy(&lcd, tl.col, tl.row);
            hd44780_puts(&lcd,tl.text.c_str());
            it++;
        }
    }
}

string I2C20x4Display::rightAlignWidth(int width, string s) {
    if(s.length() > width) {
        return s;
    }
    s.insert(s.begin(), width - s.length(), ' ');

    return s;
}
