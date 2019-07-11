#pragma once

#include "includes.h"

class ComparatorTemplate
{
public:
	virtual Estimated Compare(EstimationBase dataFromTracker) = 0;
};
