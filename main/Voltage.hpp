#pragma once
#include "Task.hpp"
#include "State.hpp"


class Voltage : public Task
{
public:
	static void startVoltageInput(void * param);
};