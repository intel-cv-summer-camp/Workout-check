//#include "preparator.h"
//#include "detector.h"
//#include "tracker.h"
//#include "comparator.h"
//#include <iostream>
//#include <string>
//
//#include "opencv2/objdetect/objdetect.hpp"
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//
//bool debug = true; // runtime debug flag
//
//using namespace std;
//using namespace cv;
//
//int main()
//{
//	// Load Face cascade (.xml file)
//	CascadeClassifier face_cascade;
//	face_cascade.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");
//	if (!face_cascade.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))
//	{
//		cerr << "Error Loading XML file" << endl;
//		return 0;
//	}
//	CascadeClassifier face_cascade_prof;
//	face_cascade_prof.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_profileface.xml");
//	if (!face_cascade_prof.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_profileface.xml"))
//	{
//		cerr << "Error Loading XML file" << endl;
//		return 0;
//	}
//	VideoCapture capture(0);
//	if (!capture.isOpened())
//		throw "Error when reading file";
//	namedWindow("window", 1);
//	for (;;)
//	{
//		Mat frame;
//		capture >> frame;
//		while (waitKey(1) < 0)
//		{
//			if (frame.empty())
//				break;
//
//			Detector_haar haar=Detector_haar(face_cascade, face_cascade_prof);
//			vector<DetectedObject> faces=haar.Detect(frame);
//
//			for (vector<DetectedObject>::iterator i = faces.begin(); i != faces.end(); ++i)
//			{
//				rectangle(dst, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
//			}
//		}
//		for (vector<DetectedObject>::iterator i = faces.begin(); i != faces.end(); ++i)
//		{
//			rectangle(frame, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width*0.75), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
//		}
//
//
//			imshow("Detected Face", frame);
//		}
//	}
//
//
//
//
//	int sourceId = 0; // corresponds to what video canal we use for input, '0' is laptop webcam
//
//	cv::Mat frame;
//	cv::VideoCapture cam(sourceId);
//
//	DetectedObject dataFromDetector;
//	EstimationBase dataFromTracker;
//	Estimated dataFromComparator;
//
//	DetectorTemplate* detector;
//	TrackerTemplate* tracker;
//	ComparatorTemplate* comparator;
//
//	/*
//	while (waitKey(1) < 0)
//	{
//		cam >> frame;
//		if (frame.empty())
//			break;
//
//		dataFromDetector = detector.Detect(frame);
//		dataFromTracker = tracker.Track(dataFromDetector);
//		dataFromComparator = comparator.Compare(dataFromTracker);
//		
//		if (dataFromComparator.isGood())
//		{
//			cout << "Excersize done correctly" << endl;
//		}
//		else
//		{
//			cout << "Excersize done incorrectly, do it again please" << endl;
//		}
//
//		if (debug)
//			imshow("WorkoutCheck", frame);
//	}*/
//	return 0;
//}
//
//#include <iostream>
//#include <string>
//
//#include "opencv2/objdetect/objdetect.hpp"
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//	// Load Face cascade (.xml file)
//	CascadeClassifier face_cascade;
//	face_cascade.load("C:/OpenCV41/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml");
//	if (!face_cascade.load("C:/OpenCV41/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml"))
//	{
//		cerr << "Error Loading XML file" << endl;
//		return 0;
//	}
//	CascadeClassifier face_cascade_prof;
//	face_cascade_prof.load("C:/OpenCV41/opencv/sources/data/haarcascades/haarcascade_profileface.xml");
//	if (!face_cascade_prof.load("C:/OpenCV41/opencv/sources/data/haarcascades/haarcascade_profileface.xml"))
//	{
//		cerr << "Error Loading XML file" << endl;
//		return 0;
//	}
//
//
//	VideoCapture capture(0);
//	if (!capture.isOpened())
//		throw "Error when reading file";
//	namedWindow("window", 1);
//	for (;;)
//	{
//		Mat frame;
//		capture >> frame;
//		while (waitKey(1) < 0)
//		{
//			if (frame.empty())
//				break;
//
//			vector<Rect> faces;
//		    face_cascade_prof.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//			if (!faces.empty())
//			for (vector<Rect>::iterator i = faces.begin(); i != faces.end(); ++i)
//			{
//				rectangle(frame, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width*0.75), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
//			}
//			if (faces.empty())
//			{
//				Mat dst;
//				int i = -45;
//				while (faces.empty())
//				{
//					Point2f src_center(frame.cols / 2.0F, frame.rows / 2.0F);
//					Mat rot_mat = getRotationMatrix2D(src_center, i, 1.0);
//
//					warpAffine(frame, dst, rot_mat, frame.size());
//					// Detect faces
//					face_cascade.detectMultiScale(dst, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//					if (i == 45) i = -45;
//					i += 45;
//				}
//			
//				for (vector<Rect>::iterator i = faces.begin(); i != faces.end(); ++i)
//				{
//					rectangle(dst, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
//				}
//			}
//				imshow("Detected Face", frame);
//		}
//	}
//	return 0;
//}



//#include <string>
//#include <iostream>
//
//#include <opencv2/core.hpp>
//#include <opencv2/highgui.hpp>
//#include <opencv2/dnn.hpp>
//
//#include "detector.h"
//
//using namespace std;
//using namespace cv;
//using namespace cv::dnn;
//
//const char* cmdAbout =
//"This is an empty application that can be treated as a template for your "
//"own doing-something-cool applications.";
//
//const char* cmdOptions =
//"{ i  image                             | <none> | image to process                  }"
//"{ w  width                             |        | image width for classification    }"
//"{ h  height                            |        | image heigth fro classification   }"
//"{ model_path                           |        | path to model                     }"
//"{ detector_path                        |        | path to model configuration       }"
//"{ mean                                 |        | vector of mean model values       }"
//"{ swap                                 |        | swap R and B channels. TRUE|FALSE }"
//"{ acc                                  |        | Threshhold accuracy for detection }"
//"{ q ? help usage                       |        | print help message                }";
//
//
//int main(int argc, const char** argv) {
//	// Parse command line arguments.
//	CommandLineParser parser(argc, argv, cmdOptions);
//	parser.about(cmdAbout);
//
//	// If help option is given, print help message and exit.
//	if (parser.get<bool>("help")) {
//		parser.printMessage();
//		return 0;
//	}
//
//	// Do something cool.
//	//Input arguments
//	String imgName(parser.get<String>("image"));
//	String model(parser.get<String>("model_path"));
//	String config(parser.get<String>("detector_path"));
//	//Mat image = imread(imgName);
//	//namedWindow("Random Picture", WINDOW_NORMAL);
//	//imshow("Random Picture", image);
//	//waitKey();
//
//	int Width(parser.get<int>("width")), Height(parser.get<int>("height"));
//	double acc(parser.get<double>("acc"));
//	Scalar mean(parser.get<int>("mean"));
//	bool swapRB(parser.get<bool>("swap"));
//	Mat frame;
//	VideoCapture cap(0);
//	Scalar meanVal(104.0, 177.0, 123.0);
//	while (waitKey(1) < 0)
//	{
//		cap >> frame;
//		if (frame.empty())
//			break;
//		DnnDetector DnnNet(model, config, Width, Height, meanVal, swapRB);
//		Mat result = DnnNet.Detect(frame);
//		cout << result.size;
//		for (int i = 0; i < result.rows; i++)
//		{
//			float confidence = result.at<float>(i, 2);
//			//cout << "\n" << confidence;
//			if (confidence > acc)
//			{
//				cout << "\n" << confidence;
//				int idx = static_cast<int>(result.at<float>(i, 1));
//				int xLeftBottom = static_cast<int>(result.at<float>(i, 3) * frame.cols);
//				int yLeftBottom = static_cast<int>(result.at<float>(i, 4) * frame.rows);
//				int xRightTop = static_cast<int>(result.at<float>(i, 5) * frame.cols);
//				int yRightTop = static_cast<int>(result.at<float>(i, 6) * frame.rows);
//				rectangle(frame, Point((int)xLeftBottom, (int)yLeftBottom), Point((int)(xRightTop),
//					(int)(yRightTop)), Scalar(0, 255, 0));
//			}
//		}
//		imshow("Frame", frame);
//	}
//	/*DnnDetector DnnNet(model, config, Width, Height, mean, swapRB);
//	Mat result = DnnNet.Detect(image);
//	cout << result.size;
//	for (int i = 0; i < result.rows; i++)
//	{
//		float confidence = result.at<float>(i, 2);
//		cout << "\n" << confidence;
//		if (confidence > acc)
//		{
//			int idx = static_cast<int>(result.at<float>(i, 1));
//			int xLeftBottom = static_cast<int>(result.at<float>(i, 3) * image.cols);
//			int yLeftBottom = static_cast<int>(result.at<float>(i, 4) * image.rows);
//			int xRightTop = static_cast<int>(result.at<float>(i, 5) * image.cols);
//			int yRightTop = static_cast<int>(result.at<float>(i, 6) * image.rows);
//			rectangle(image, Point((int)xLeftBottom, (int)yLeftBottom),Point((int)(xRightTop),
//				(int)(yRightTop)), Scalar(0, 255, 0));
//		}
//	}*/
//	//cout << result.reshape(1,100);
//	//cout << result <<"\n";
//	//rectangle(image, Point(100, 200), Point(200, 100), Scalar(0, 255, 0));
//	//imshow("Frame", frame);
//	waitKey();
//
//	return 0;
//}

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

const size_t inWidth = 300;
const size_t inHeight = 300;
const double inScaleFactor = 1.0;
const float confidenceThreshold = 0.7;
const cv::Scalar meanVal(104.0, 177.0, 123.0);

#define CAFFE

const std::string caffeConfigFile = "C:/Users/temp2019/Desktop/CV_Camp/awesome-face-detection-master/models/deploy.prototxt.txt";
const std::string caffeWeightFile = "C:/Users/temp2019/Desktop/CV_Camp/awesome-face-detection-master/models/res10_300x300_ssd_iter_140000_fp16.caffemodel";

const std::string tensorflowConfigFile = "./models/opencv_face_detector.pbtxt";
const std::string tensorflowWeightFile = "./models/opencv_face_detector_uint8.pb";

void detectFaceOpenCVDNN(Net net, Mat &frameOpenCVDNN)
{
	int frameHeight = frameOpenCVDNN.rows;
	int frameWidth = frameOpenCVDNN.cols;
#ifdef CAFFE
	cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, false, false);
#else
	cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, true, false);
#endif

	net.setInput(inputBlob, "data");
	cv::Mat detection = net.forward("detection_out");

	cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

	for (int i = 0; i < detectionMat.rows; i++)
	{
		float confidence = detectionMat.at<float>(i, 2);

		if (confidence > confidenceThreshold)
		{
			int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);
			int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);
			int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);
			int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);

			cv::rectangle(frameOpenCVDNN, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0), 2, 4);
		}
	}

}


int main(int argc, const char** argv)
{
#ifdef CAFFE
	Net net = cv::dnn::readNetFromCaffe(caffeConfigFile, caffeWeightFile);
#else
	Net net = cv::dnn::readNetFromTensorflow(tensorflowWeightFile, tensorflowConfigFile);
#endif

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
		detectFaceOpenCVDNN(net, frame);
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