#ifndef STATE_H
#define STATE_H
#include <string>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "pins.h"

enum Band { b160m, b80m, b60m, b40m, b30m, b20m, b17m, b15m, b12m, b10m, b6m };

struct StateData {
    double voltage;
    double current;
    double power;
    double swr;
    double temp;
    Band band;
    std::string status;
    std::string mode;
};

class StateController {
    protected:
        static StateData stateData;
    public: 
        static const char* STATE_ERROR_SWR;
        static const char* STATE_ERROR_LPF;
        static const char* STATE_ERROR_VOLTS_LOW;
        static const char* STATE_ERROR_VOLTS_HIGH;
        static const char* STATE_ERROR_TEMP_HIGH;
        static const char* STATE_ERROR_TEMP_SENSOR;
        static const char* STATE_ERROR_CURRENT_HIGH;
        static const char* STATE_TRANSMITTING;
        static const char* STATE_RECEIVING;
        static const char* STATE_STANDBY;
        static const char* MODE_MANUAL;
        static const char* MODE_AUTOMATIC;
        static const char* MODE_ERROR;

        static const double VOLTAGE_MAX;

        static StateData getFullState();
        static void startSafetyMonitor(void* params);
        static void startVoltageMonitor(void*);
        static void setup();
};

#endif