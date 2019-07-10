#include <stdio.h>
#include <iostream>

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

bool debug = true; // runtime debug flag

using namespace std;
using namespace cv;

int main()
{
	cout << "Enter SourceId (int): ";
	int sourceId; // corresponds to what video canal we use for input
	cin >> sourceId; 

	cv::Mat frame;
	cv::VideoCapture cam(sourceId);
	while (waitKey(1) < 0)
	{
		cam >> frame;
		if (frame.empty())
			break;
		/*
		сюда кодик пишем :)


		*/
		if (debug)
			imshow("hi", frame);
	}
	return 0;
}