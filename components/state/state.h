#ifndef STATE_H
#define STATE_H
#include <string>

enum Band { b160m, b80m, b60m, b40m, b30m, b20m, b17m, b15m, b12m, b10m, b6m };

struct StateData {
    double frequency;
    double volts;
    double amps;
    double swr;
    double temp;
    Band band;
    std::string state;
};

class State {
    protected:
        StateData stateData;
    public: 
        static const constexpr char* STATE_ERROR_SWR = "ERROR_SWR";
        static const constexpr char* STATE_ERROR_LPF = "ERROR_LPF";
        static const constexpr char* STATE_ERROR_VOLTS_LOW = "ERROR_VOLTS_LOW";
        static const constexpr char* STATE_ERROR_VOLTS_HIGH = "ERROR_VOLTS_HIGH";
        static const constexpr char* STATE_ERROR_TEMP_HIGH = "ERROR_TEMP_HIGH";
        static const constexpr char* STATE_ERROR_TEMP_SENSOR = "ERROR_TEMP_SENSOR";
        static const constexpr char* STATE_TRANSMITTING = "TRANSMITTING";
        static const constexpr char* STATE_RECEIVING = "RECEIVING";
        static const constexpr char* STATE_STANDBY = "STANDBY";

        StateData getFullState();

        State();
};

#endif