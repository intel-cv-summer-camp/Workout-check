#pragma once

#include <stdio.h>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

class Preparator
{
public:
	Preparator(int sourceId = 0); // 0 id corresponds to laptop's webcam
	cv::Mat Run();

private:
	int sourceId;
};
