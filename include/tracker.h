#pragma once

#include "includes.h"

class TrackerTemplate
{
public:
	virtual Data Track(Data dataFromDetector) = 0;
};

class Tracker : public TrackerTemplate
{

};