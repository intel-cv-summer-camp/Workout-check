#pragma once

#include "includes.h"

class ComparatorTemplate
{
public:
	virtual Data Compare(Data dataFromTracker) = 0;
};

class Comparator : public ComparatorTemplate
{

};