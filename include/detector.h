#pragma once
#include "includes.h"
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


class DetectorTemplate
{
public:
	virtual vector<DetectedObject> detectFaceOpenCVDNN(Net net, Mat &frameOpenCVDNN) = 0;
};
class Detector :public DetectorTemplate 
{
	const size_t inWidth = 300;
	const size_t inHeight = 300;
	const double inScaleFactor = 1.0;
	const float confidenceThreshold = 0.7;
	const cv::Scalar meanVal = { 104.0, 177.0, 123.0 };
	string caffeConfigFile;
	string caffeWeightFile;
	Point2f ideal_center;
public:
	Detector(string caffeConfigFile_, string caffeWeightFile_);
	vector<DetectedObject> detectFaceOpenCVDNN(Net net, Mat &frameOpenCVDNN);
	Mat detectFaceLocation(Mat &frameOpenCVDNN);
	Mat detectFaceLocation1(Mat &frameOpenCVDNN);
};