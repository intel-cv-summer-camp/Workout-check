#pragma once

#include "includes.h"

class TrackerTemplate
{
public:
	virtual EstimationBase Track(DetectedObject dataFromDetector) = 0;
};
