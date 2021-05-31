#ifndef STATE_H
#define STATE_H
#include <string>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Display.hpp"

#include "pins.hpp"

using namespace std;

static TaskHandle_t stateControllerHandle = NULL;


enum Band { b160m, b80m, b60m, b40m, b30m, b20m, b17m, b15m, b12m, b10m, b6m };
const string BandToString(Band v);

struct StateData {
    double voltage;
    double current;
    double power;
    double swr;
    double temp;
    Band band;
    const char* status;
    const char* mode;
};

class StateController {
    protected:
        static StateData stateData;
    public:

        static const double VOLTAGE_MAX;

        static StateData getFullState();
        static void startSafetyMonitor(void* params);
        static void startVoltageMonitor(void*);
        static void setup();
};

#endif