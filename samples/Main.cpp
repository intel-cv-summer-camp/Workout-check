#include "preparator.h"
#include "detector.h"
#include "tracker.h"
#include "comparator.h"

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>

#include <fstream>

using namespace cv;
using namespace std;
using namespace cv::dnn;



#define CAFFE

const std::string caffeConfigFile = "C:/Users/temp2019/Desktop/Workout-check/random_nnet/deploy.prototxt.txt";
const std::string caffeWeightFile = "C:/Users/temp2019/Desktop/Workout-check/random_nnet/res10_300x300_ssd_iter_140000_fp16.caffemodel";

int main(int argc, const char** argv)
{
#ifdef CAFFE
	Net net = cv::dnn::readNet(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif
	Detector det = Detector(caffeConfigFile, caffeWeightFile);
	VideoCapture source("C:/Users/temp2019/Desktop/Workout-check/execises/test_3.mp4");
	Mat frame;
	double tt_opencvDNN = 0;
	double fpsOpencvDNN = 0;
	int dif;
	while (1)
	{
		source >> frame;
		if (frame.empty())
			break;
		double t = cv::getTickCount();
		vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame);
		comparison ex = comparison();
		dif = ex.Compare_ex_3(vect);
		for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
		{
			rectangle(frame, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);
			line(frame, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(255, 0, 0), 2);
		}
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
		}
	}
	if (dif>2)
	{
		cout << "Try again!" << endl;
	}
	else
	{
		cout << "Good Job! Next one!" << endl;
		VideoCapture cap("C:/Users/temp2019/Desktop/Workout-check/execises/test_2.mp4");
		Mat frame1;
		int correct = 0; 
		while (1)
		{
			cap >> frame1;
			if (frame1.empty())
				break;
			double t = cv::getTickCount();
			vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame1);
			comparison ex = comparison();
			correct== ex.Compare_ex_2(vect);
			for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
			{
				rectangle(frame1, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);
				line(frame1, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(255, 0, 0), 2);
			}
			imshow("OpenCV - DNN Face Detection", frame1);
			int k = waitKey(5);
			if (k == 27)
			{
				destroyAllWindows();
			}
		}
		if (correct > 0)
			cout << "Good Job! Next one!" << endl;
		else
		{
			cout << "Try again!" << endl;
		}
	}
	waitKey();
	return 0;
}