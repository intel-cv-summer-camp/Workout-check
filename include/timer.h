#pragma once

#include "includes.h"

class Timer
{
public:
	uint32_t SetTimer()
	{
		this->start_time = clock();
	}
	uint32_t GetTime()
	{
		uint32_t end_time = clock();
		uint32_t result = start_time - end_time;
		start_time = end_time;
		return result;
	}
private:
	unsigned int start_time;
};