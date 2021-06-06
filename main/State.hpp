#pragma once
#include <string>
#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Display.hpp"
#include "Task.hpp"
#include "messages.hpp"

#include "pins.hpp"
enum Band : u_int8_t { b160m, b80m, b60m, b40m, b30m, b20m, b17m, b15m, b12m, b10m, b6m } ;


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

class State {
protected:
	static StateData stateData;
	static TaskHandle_t displayHandle, voltageInputHandle, safetyMonitorHandle, tempMonitorHandle;
public:
	
	static StateData getFullState();
	
	static void transmit();
	static void receive();
	
	static TaskHandle_t getVoltageInputHandle(), getSafetyMonitorHandle(), getDisplayHandle(), getTempMonitorHandle();
	static void setVoltage(double v);
	static void setMode(const char*);
	static void setStatus(const char*);
	static void setTemp(double t);
	static Band setBandUp();
	static Band setBandDown();
	
	static void setup(TaskHandle_t dH, TaskHandle_t vH, TaskHandle_t sMH, TaskHandle_t tmH);
};
	