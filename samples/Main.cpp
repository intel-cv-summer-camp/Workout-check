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

	double t = cv::getTickCount();

	VideoCapture source;
	if (argc == 1)
		source.open(0);
	else
		source.open(argv[1]);
	Mat frame;

	double tt_opencvDNN = 0;
	double fpsOpencvDNN = 0;
	CascadeClassifier face_cascade;
	face_cascade.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml");
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
			vector<Rect> faces;
			face_cascade.detectMultiScale(frame, faces, 1.5, 3, 0 | CASCADE_SCALE_IMAGE, Size(15, 15));
			for (vector<Rect>::iterator i = faces.begin(); i != faces.end(); ++i)
			{
				rectangle(frame, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width*0.75), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
			}
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
			break;
		}
	}
}