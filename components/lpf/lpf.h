#include <map>
#include "state.h"
#include <driver/gpio.h>

class LPF
{
protected:
    int lpfPins[3];
    typedef struct LPFSwitches
    {
        bool relay[3];
    } LPFSwitches;
    std::map<State::Band, LPFSwitches> bandMapping
    {
        {State::Band::b160m, {true, true, true}},
        {State::Band::b80m, {false, false, false}},
        {State::Band::b60m, {false, false, true}},
        {State::Band::b40m, {false, true, false}},
        {State::Band::b30m, {false, true, false}},
        {State::Band::b20m, {false, true, true}},
        {State::Band::b17m, {false, true, true}},
        {State::Band::b15m, {true, false, false}},
        {State::Band::b12m, {true, false, false}},
        {State::Band::b10m, {true, false, false}},
        {State::Band::b6m, {true, false, true}},
    };

public:
    LPF(int pin1, int pin2, int pin3);
};