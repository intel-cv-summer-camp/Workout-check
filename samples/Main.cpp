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

#include <iostream>
#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

int main()
{
	// Load Face cascade (.xml file)
	CascadeClassifier face_cascade;
	face_cascade.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml");
	if (!face_cascade.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_alt.xml"))
	{
		cerr << "Error Loading XML file" << endl;
		return 0;
	}
	CascadeClassifier face_cascade_prof;
	face_cascade_prof.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_profileface.xml");
	if (!face_cascade_prof.load("C:\\My foulder\\Resourses\\opencv\\opencv\\sources\\data\\haarcascades\\haarcascade_profileface.xml"))
	{
		cerr << "Error Loading XML file" << endl;
		return 0;
	}


	VideoCapture capture(0);
	if (!capture.isOpened())
		throw "Error when reading file";
	namedWindow("window", 1);
	for (;;)
	{
		Mat frame;
		capture >> frame;
		while (waitKey(1) < 0)
		{
			if (frame.empty())
				break;

			vector<Rect> faces;
		    face_cascade_prof.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
			if (faces.empty())
			{
				Mat dst;
				int i = -45;
				while (faces.empty())
				{
					Point2f src_center(frame.cols / 2.0F, frame.rows / 2.0F);
					Mat rot_mat = getRotationMatrix2D(src_center, i, 1.0);

					warpAffine(frame, dst, rot_mat, frame.size());
					// Detect faces
					face_cascade.detectMultiScale(dst, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
					if (i == 45) i = -45;
					i += 45;
				}
			
				for (vector<Rect>::iterator i = faces.begin(); i != faces.end(); ++i)
				{
					rectangle(dst, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
				}
			}
			for (vector<Rect>::iterator i = faces.begin(); i != faces.end(); ++i)
			{
				rectangle(frame, Point2i((int)((*i).x), (int)((*i).y)), Point2i((int)((*i).x + (*i).width*0.75), (int)((*i).y + (*i).height)), cv::Scalar(0, 255, 0), 2);
			}
				imshow("Detected Face", frame);
		}
	}
	return 0;
}
