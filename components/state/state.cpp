#include "state.h"

State::State() {

    stateData = StateData{
        21.33,
        19.33,
        100.33,
        1.9944,
        32.11,
        Band::b160m,
        STATE_ERROR_SWR,
        MODE_AUTOMATIC
    };
}

StateData State::getFullState() {
    return stateData;
}