#pragma once

#include "includes.h"

class DetectorTemplate
{
public:
	virtual DetectedObject Detect(cv::Mat image) = 0;
};
