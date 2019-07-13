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

const std::string caffeConfigFile = "C:/Users/Валентин/Desktop/Workout-check/random_nnet/deploy.prototxt.txt";
const std::string caffeWeightFile = "C:/Users/Валентин/Desktop/Workout-check/random_nnet/res10_300x300_ssd_iter_140000_fp16.caffemodel";

int main(int argc, const char** argv)
{
#ifdef CAFFE
	Net net = cv::dnn::readNet(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif
	Detector det = Detector(caffeConfigFile, caffeWeightFile);
	VideoCapture source("C:/Users/Валентин/Desktop/Workout-check/execises/test_3.mp4");
	Mat frame;
	double tt_opencvDNN = 0;
	double fpsOpencvDNN = 0;
	int o = 0;
	int prev = 0;
	int min=0;
	while (1)
	{
		source >> frame;
		if (frame.empty())
			break;
		double t = cv::getTickCount();
		vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame);
		for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
		{
			rectangle(frame, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);
			line(frame, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(255, 0, 0), 2);
			int line = sqrt((((int)((*i).Right)) - ((int)((*i).Left)))*(((int)((*i).Right)) - ((int)((*i).Left))) + (((int)((*i).Bottom)) - ((int)((*i).Top)))*(((int)((*i).Bottom)) - ((int)((*i).Top))));
			if (line > prev)
				o++;
			else if (line < prev)
				o--;
			prev = line;
		}
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
		}
		
	}
	if (o == 0)
		cout << "Good Job! Next one!" << endl;
	VideoCapture cap("C:/Users/Валентин/Desktop/Workout-check/execises/test_2.mp4");
	Mat frame1;
	int correct = 0;
	while (1)
	{
		cap >> frame1;
		if (frame1.empty())
			break;
		double t = cv::getTickCount();
		vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame1);
		for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
		{
			rectangle(frame1, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);
			line(frame1, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(255, 0, 0), 2);
			cout << (int)((*i).Left) << "\t" << (int)((*i).Right) << "\t" << (int)((*i).Top) << "\t" << (int)((*i).Bottom) << endl;
			comparison ex = comparison();
			int right = ex.Compare((int)((*i).Left), (int)((*i).Top), (int)((*i).Right), (int)((*i).Bottom));
			if (right > 0)
				correct += right;
		}
		cout << "correct = " << correct;
		imshow("OpenCV - DNN Face Detection", frame1);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
		}
	}
}