#pragma once

#include "includes.h"

class DetectorTemplate
{
public:
	virtual Data Detect(cv::Mat image) = 0;
};

class Detector : public DetectorTemplate
{
	
};