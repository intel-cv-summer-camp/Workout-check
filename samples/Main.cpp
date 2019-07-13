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
#include "opencv2/objdetect/objdetect.hpp"


using namespace cv;
using namespace std;
using namespace cv::dnn;


#define CAFFE

const std::string caffeConfigFile = "./../../Workout-check/random_nnet/deploy.prototxt.txt";
const std::string caffeWeightFile = "./../../Workout-check/random_nnet/res10_300x300_ssd_iter_140000_fp16.caffemodel";

int main(int argc, const char** argv)
{
	
#ifdef CAFFE
	Net net = cv::dnn::readNet(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif

	//Detector det = Detector(caffeConfigFile, caffeWeightFile);
	Comparator_ex1 comp = Comparator_ex1();

	//double t = cv::getTickCount();

	//VideoCapture source("./../../../Workout-check/videos/123.mp4");
	/*if (argc == 1)
		source.open(0);
	else
		source.open(argv[1]);*/
	/*Mat frame;
	while (1)
	{
		source >> frame;
		if (frame.empty())
			break;
		double t = cv::getTickCount();
		vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame);
		for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
		{
			Point center(((int)((*i).Left)+ (int)((*i).Top))/2.0,((int)((*i).Right)+ (int)((*i).Bottom))/2.0);
			rectangle(frame, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);

		}
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
			break;
		}
	}*/
}