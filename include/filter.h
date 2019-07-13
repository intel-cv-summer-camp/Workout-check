#pragma once
#include <iostream>
#include <string>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

class Filter
{
    public:
		Mat	GrayFilter(Mat image);
		Mat ResizeFilter(Mat image, int newWidth, int newHeight, int type);
};