#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

class Task
{
private:
	static TaskHandle_t taskHandle;
public:
	static TaskHandle_t getTaskHandle();
	
};
