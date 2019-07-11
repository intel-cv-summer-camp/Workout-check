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

using namespace cv;
using namespace std;
using namespace cv::dnn;



#define CAFFE

const std::string caffeConfigFile = "C:/Users/Валентин/Desktop/Workout-check/random_nnet/deploy.prototxt.txt";
const std::string caffeWeightFile = "C:/Users/Валентин/Desktop/Workout-check/random_nnet/res10_300x300_ssd_iter_140000_fp16.caffemodel";

int main(int argc, const char** argv)
{
#ifdef CAFFE
	Net net = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif

	Detector det = Detector(caffeConfigFile, caffeWeightFile);

	VideoCapture source;
	if (argc == 1)
		source.open(0);
	else
		source.open(argv[1]);
	Mat frame;

	double tt_opencvDNN = 0;
	double fpsOpencvDNN = 0;
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
		}
		//tt_opencvDNN = ((double)cv::getTickCount() - t) / cv::getTickFrequency();
		//fpsOpencvDNN = 1 / tt_opencvDNN;
		//putText(frame, format("OpenCV DNN ; FPS = %.2f", fpsOpencvDNN), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1.4, Scalar(0, 0, 255), 4);
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
			break;
		}
	}
}