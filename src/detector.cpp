#pragma once
#include "detector.h"
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

Detector :: Detector(string caffeConfigFile_, string caffeWeightFile_)
{
	caffeConfigFile = caffeConfigFile_;
	caffeWeightFile = caffeWeightFile_;
}

vector<DetectedObject> Detector :: detectFaceOpenCVDNN(Net net, Mat &frameOpenCVDNN)
{
	int frameHeight = frameOpenCVDNN.rows;
	int frameWidth = frameOpenCVDNN.cols;
#ifdef CAFFE
	cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, false, false);
#else
	Mat inputBlob = blobFromImage(frameOpenCVDNN, inScaleFactor, Size(inWidth, inHeight), meanVal, true, false);
#endif
	net.setInput(inputBlob, "data");
	cv::Mat detection = net.forward("detection_out");
	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());
	vector<DetectedObject> result_;
	for (int i = 0; i < detectionMat.rows; i++)
	{
		float confidence = detectionMat.at<float>(i, 2);
		if (confidence > confidenceThreshold)
		{
			DetectedObject obj;
			obj.Left = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
			obj.Top = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
			obj.Right = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
			obj.Bottom = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);
			result_.push_back(obj);
		}
	}

	ideal_center=Point2f(frameOpenCVDNN.cols / 2.0F, frameOpenCVDNN.rows / 2.0F);
	
	return result_;
}

Mat Detector::detectFaceLocation(Mat &frameOpenCVDNN)
{
	Mat dst;
	Mat rot_mat = getRotationMatrix2D(ideal_center, -60, 1.0);
	warpAffine(frameOpenCVDNN, dst, rot_mat, frameOpenCVDNN.size());
	return dst;
}

Mat Detector::detectFaceLocation1(Mat &frameOpenCVDNN)
{
	Mat dst;
	Mat rot_mat = getRotationMatrix2D(ideal_center, 60, 1.0);
	warpAffine(frameOpenCVDNN, dst, rot_mat, frameOpenCVDNN.size());
	imshow("", dst);
	return dst;
}