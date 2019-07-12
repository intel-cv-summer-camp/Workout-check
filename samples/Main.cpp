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

const std::string caffeConfigFile = "C:/Users/temp2019/Desktop/CV_Camp/Разминка/Workout-check/random_nnet/deploy.prototxt.txt";
const std::string caffeWeightFile = "C:/Users/temp2019/Desktop/CV_Camp/Разминка/Workout-check/random_nnet/res10_300x300_ssd_iter_140000_fp16.caffemodel";

int main(int argc, const char** argv)
{
#ifdef CAFFE
	Net net = cv::dnn::readNet(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif

	Detector det = Detector(caffeConfigFile, caffeWeightFile);

	VideoCapture source("C:/Users/temp2019/Desktop/CV_Camp/Разминка/videos/Video.mkv");
	Mat frame;

	double tt_opencvDNN = 0;
	double fpsOpencvDNN = 0;
	ofstream myfile;
	myfile.open("ex_3_angles.txt", ios::app);
	while (1)
	{
		source >> frame;
		if (frame.empty())
			break;
		double t = cv::getTickCount();
		vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame);
		for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
		{
			rectangle(frame, Point((int)((*i).Left), (int)((*i).Right)), Point((int)((*i).Top), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);
			line(frame, Point((int)((*i).Left), (int)((*i).Right)), Point((int)((*i).Top), (int)((*i).Bottom)), cv::Scalar(255, 0, 0), 2);
			if (myfile.is_open())
			{
				cout << (int)((*i).Left) << "\t" << (int)((*i).Right) << "\t" << (int)((*i).Top) << "\t" << (int)((*i).Bottom) << endl;
				myfile << (int)((*i).Left) << "\t" << (int)((*i).Right) << "\t" << (int)((*i).Top) << "\t" << (int)((*i).Bottom) << endl;
				//myfile << (int)((*i).Left) << (int)((*i).Right) << (int)((*i).Top) << (int)((*i).Bottom) << "\n";
			}

		}
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
			break;
		}
	}
	myfile.close();
}