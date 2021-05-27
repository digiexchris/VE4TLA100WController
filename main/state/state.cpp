#include "state.h"

State::State() {

	stateData = {
		.voltage = 21.33,
		.current = 19.33,
		.power = 100.33,
		.swr = 1.9944,
		.temp = 32.11,
		.band = Band::b160m,
		.status = STATE_ERROR_SWR,
		.mode = MODE_AUTOMATIC
	};
}

StateData State::getFullState() {
	return stateData;
}
