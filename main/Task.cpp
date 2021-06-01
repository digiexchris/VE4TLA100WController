#include "Task.hpp"

TaskHandle_t Task::taskHandle = NULL;

TaskHandle_t* Task::getTaskHandle() {
	return &taskHandle;
}