#include "state.h"

State::State() {

    stateData = StateData{
        19999999,
        21.33,
        19.33,
        1.9944,
        32.11,
        Band::b160m,
        STATE_TRANSMITTING,
    };
}

StateData State::getFullState() {
    return stateData;
}