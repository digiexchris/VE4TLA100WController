#pragma once

#include <ds18x20.h>
#include "Task.hpp"
#include "pins.hpp"
#include "State.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


class TempMonitor : public Task
{
public:
	static void startTempMonitor(void * param);
};