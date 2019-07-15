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
//const std::string caffeConfigFile = "C:/Users/temp2019/Desktop/Workout-check/random_nnet/deploy.prototxt.txt";
//const std::string caffeWeightFile = "C:/Users/temp2019/Desktop/Workout-check/random_nnet/res10_300x300_ssd_iter_140000_fp16.caffemodel";

int main(int argc, const char** argv)
{
	
#ifdef CAFFE
	Net net = cv::dnn::readNet(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif
	Detector det = Detector(caffeConfigFile, caffeWeightFile);
	Comparator_ex1 comp1 = Comparator_ex1();
	double t = cv::getTickCount();
	vector <int> left_vec, top_vec, right_vec, bot_vec;

	VideoCapture source("./../../Workout-check/execises/ex_32.mkv");
	Mat frame;
	double tt_opencvDNN = 0;
	double fpsOpencvDNN = 0;
	int dif, correct;
	while (1)
	{
		source >> frame;
		if (frame.empty())
			break;
		double t = cv::getTickCount();
		vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame);
		comparison_ex2 ex2 = comparison_ex2();
		dif = ex2.Compare(vect);
		comparison_ex3 ex3 = comparison_ex3();
		correct = ex3.Compare(vect);
		for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
		{
			Point center(((int)((*i).Left)+ (int)((*i).Top))/2.0,((int)((*i).Right)+ (int)((*i).Bottom))/2.0);
			left_vec.push_back((int)((*i).Left));
			top_vec.push_back((int)((*i).Top));
			right_vec.push_back((int)((*i).Right));
			bot_vec.push_back((int)((*i).Bottom));

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
	int* left = &left_vec[0];
	int* top = &top_vec[0];
	int* right = &right_vec[0];
	int* bot = &bot_vec[0];

	int errors1 = comp1.Compare(left, top, right, bot);
	if (errors1 < 20)
		cout << endl << "Exercise 1: Good Job!" << endl;
	else if (correct > 0)
		cout << endl << "Exercise 3: Good Job!" << endl;
	else if (dif > 2)
		cout << endl << "Try harder!" << endl;
	else
		cout << endl << "Exercise 2: Good Job!" << endl;
	//if (dif>2)
	//{
	//	cout << "Try again! D;" << endl;
	//}
	//else
	//{
	//	cout << "Good Job! Next one!" << endl;
	//	cout << "Exercise 3: ";
	//	//VideoCapture source("C:/Users/temp2019/Desktop/Workout-check/execises/test_2.mp4");
	//	///*Mat frame1;
	//	//int correct = 0; 
	//	//while (1)
	//	//{
	//	//	source >> frame1;
	//	//	if (frame1.empty())
	//	//		break;
	//	//	double t = cv::getTickCount();
	//	//	vector<DetectedObject> vect = det.detectFaceOpenCVDNN(net, frame1);
	//	//	comparison_ex3 ex3 = comparison_ex3();
	//	//	correct = ex3.Compare(vect);
	//	//	for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
	//	//	{
	//	//		rectangle(frame1, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(0, 255, 0), 3);
	//	//		line(frame1, Point((int)((*i).Left), (int)((*i).Top)), Point((int)((*i).Right), (int)((*i).Bottom)), cv::Scalar(255, 0, 0), 2);
	//	//	}
	//	//	imshow("OpenCV - DNN Face Detection", frame1);
	//	//	int k = waitKey(5);
	//	//	if (k == 27)
	//	//	{
	//	//		destroyAllWindows();
	//	//	}
	//	//}*/
	//	if (correct > 0)
	//		cout << "Good Job! Next one!" << endl;
	//	else
	//	{
	//		cout << "Try again! D;" << endl;
	//	}
	//}
	waitKey();
	return 0;
}