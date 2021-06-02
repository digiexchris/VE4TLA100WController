#pragma once
#include <string>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Display.hpp"
#include "Task.hpp"
#include "State.hpp"

#include "pins.hpp"

using namespace std;


class SafetyMonitor : public Task {
protected:
	static TaskHandle_t displayHandle;
public:
    static const double VOLTAGE_MAX;

    static void startSafetyMonitor(void* params);
    static void startVoltageInput(void*);
	static void setup(TaskHandle_t dH);
	
};