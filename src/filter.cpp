#include "filter.h"

Mat Filter::GrayFilter(Mat image)
{
	cvtColor(image, image, COLOR_BGR2GRAY);
	return image;
}

Mat Filter::ResizeFilter(Mat image, int newWidth, int newHeight, int type)
{
	Mat temp(newWidth, newHeight, type);
	resize(image, temp, temp.size(), 0, 0, INTER_LINEAR);
	return temp;
}
