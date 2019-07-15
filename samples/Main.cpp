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

	Detector det = Detector(caffeConfigFile, caffeWeightFile);
	Comparator_ex1 comp1 = Comparator_ex1();
	Comparator_ex3 comp3 = Comparator_ex3();
	Comparator_ex2 comp2 = Comparator_ex2();

	////
	//string line;
	//int left0[115], top0[115], right0[115], bot0[115];
	//ifstream myfile("./../../Workout-check/execises/ex_1_left-right.txt");
	//if (myfile.is_open())
	//{
	//	int i = 0;
	//	while (getline(myfile, line))
	//	{
	//		//cout << line << '\n';
	//		left0[i] = stoi(line.substr(0, 3));
	//		//cout << stoi(line.substr(0,3)) << "\n";
	//		top0[i] = stoi(line.substr(4, 3));
	//		right0[i] = stoi(line.substr(8, 3));
	//		bot0[i] = stoi(line.substr(12, 3));
	//		i++;
	//	}
	//	myfile.close();
	//}
	//int errors0 = comp1.Compare(left0, top0, right0, bot0);
	//cout << "\n" << "estimated errors0 = " << errors0 << "\n";

	double t = cv::getTickCount();

	VideoCapture source("./../../videos/Video(4).mkv");
	/*if (argc == 1)
		source.open(0);
	else
		source.open(argv[1]);*/
	Mat frame;
	vector <int> left_vec, top_vec, right_vec, bot_vec;
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
			left_vec.push_back((int)((*i).Left));
			top_vec.push_back((int)((*i).Top));
			right_vec.push_back((int)((*i).Right));
			bot_vec.push_back((int)((*i).Bottom));

		}
		imshow("OpenCV - DNN Face Detection", frame);
		int k = waitKey(5);
		if (k == 27)
		{
			destroyAllWindows();
			break;
		}
	}
	//cout <<"\n"<< j << "\n";
	int* left = &left_vec[0];
	int* top = &top_vec[0];
	int* right = &right_vec[0];
	int* bot = &bot_vec[0];
	//int errors1 = comp1.Compare(left, top, right, bot);
	//cout << "estimated errors ex1 = " << errors1 << "/n";
	//int errors2 = comp2.Compare(left, top, right, bot);
	//cout << "estimated errors ex2 = " << errors2;

	int errors3 = comp3.Compare(left, top, right, bot);
	//cout << "estimated errors ex3 = " << errors3;
	if (errors3 > 20)
		cout << "Try again! D;";
	else
		cout << "Good job!";
	waitKey();

}