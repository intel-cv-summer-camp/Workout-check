#pragma once

#include "includes.h"

class Timer
{
public:
	void SetTimer()
	{
		this->start_time = clock();
	}
	double GetTime()
	{
		clock_t end_time = clock();
		double result = (double)(end_time-start_time)/CLOCKS_PER_SEC;
		start_time = clock();
		return result;
	}
private:
	clock_t start_time;
};