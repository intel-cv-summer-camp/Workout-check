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
#include "filter.h"

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






//int H_MIN = 0;
//int H_MAX = 256;
//int S_MIN = 0;
//int S_MAX = 256;
//int V_MIN = 0;
//int V_MAX = 256;
//const int FRAME_WIDTH = 640;
//const int FRAME_HEIGHT = 480;
//const int MAX_NUM_OBJECTS = 50;
//const int MIN_OBJECT_AREA = 20 * 20;
//const int MAX_OBJECT_AREA = FRAME_HEIGHT * FRAME_WIDTH / 1.5;
//
//
//void on_trackbar(int, void*)
//{//This function gets called whenever a
//	// trackbar position is changed
//}
//
//
//void morphOps(Mat &thresh) {
//
//	//create structuring element that will be used to "dilate" and "erode" image.
//	//the element chosen here is a 3px by 3px rectangle
//
//	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
//	//dilate with larger element so make sure object is nicely visible
//	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));
//
//	erode(thresh, thresh, erodeElement);
//	erode(thresh, thresh, erodeElement);
//
//
//	dilate(thresh, thresh, dilateElement);
//	dilate(thresh, thresh, dilateElement);
//}
//
//
//string intToString(int number) {
//
//
//	std::stringstream ss;
//	ss << number;
//	return ss.str();
//}
//
//void createTrackbars() {
//	//create window for trackbars
//	string trackbarWindowName = "Now you will see magic";
//
//	namedWindow(trackbarWindowName, 0);
//	//create memory to store trackbar name on window
//	char TrackbarName[50];
//	sprintf(TrackbarName, "H_MIN", H_MIN);
//	sprintf(TrackbarName, "H_MAX", H_MAX);
//	sprintf(TrackbarName, "S_MIN", S_MIN);
//	sprintf(TrackbarName, "S_MAX", S_MAX);
//	sprintf(TrackbarName, "V_MIN", V_MIN);
//	sprintf(TrackbarName, "V_MAX", V_MAX);
//	//create trackbars and insert them into window
//	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
//	//the max value the trackbar can move (eg. H_HIGH), 
//	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
//	//                                  ---->    ---->     ---->      
//	createTrackbar("H_MIN", trackbarWindowName, &H_MIN, H_MAX, on_trackbar);
//	createTrackbar("H_MAX", trackbarWindowName, &H_MAX, H_MAX, on_trackbar);
//	createTrackbar("S_MIN", trackbarWindowName, &S_MIN, S_MAX, on_trackbar);
//	createTrackbar("S_MAX", trackbarWindowName, &S_MAX, S_MAX, on_trackbar);
//	createTrackbar("V_MIN", trackbarWindowName, &V_MIN, V_MAX, on_trackbar);
//	createTrackbar("V_MAX", trackbarWindowName, &V_MAX, V_MAX, on_trackbar);
//}
//
//void drawObject(int x, int y, Mat &frame) {
//
//	//use some of the openCV drawing functions to draw crosshairs
//	//on your tracked image!
//
//	//UPDATE:JUNE 18TH, 2013
//	//added 'if' and 'else' statements to prevent
//	//memory errors from writing off the screen (ie. (-25,-25) is not within the window!)
//
//	circle(frame, Point(x, y), 20, Scalar(0, 255, 0), 2);
//	if (y - 25 > 0)
//		line(frame, Point(x, y), Point(x, y - 25), Scalar(0, 255, 0), 2);
//	else line(frame, Point(x, y), Point(x, 0), Scalar(0, 255, 0), 2);
//	if (y + 25 < FRAME_HEIGHT)
//		line(frame, Point(x, y), Point(x, y + 25), Scalar(0, 255, 0), 2);
//	else line(frame, Point(x, y), Point(x, FRAME_HEIGHT), Scalar(0, 255, 0), 2);
//	if (x - 25 > 0)
//		line(frame, Point(x, y), Point(x - 25, y), Scalar(0, 255, 0), 2);
//	else line(frame, Point(x, y), Point(0, y), Scalar(0, 255, 0), 2);
//	if (x + 25 < FRAME_WIDTH)
//		line(frame, Point(x, y), Point(x + 25, y), Scalar(0, 255, 0), 2);
//	else line(frame, Point(x, y), Point(FRAME_WIDTH, y), Scalar(0, 255, 0), 2);
//
//	putText(frame, intToString(x) + "," + intToString(y), Point(x, y + 30), 1, 1, Scalar(0, 255, 0), 2);
//
//}
//
//void trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed) {
//
//	Mat temp;
//	threshold.copyTo(temp);
//	//these two vectors needed for output of findContours
//	vector< vector<Point> > contours;
//	vector<Vec4i> hierarchy;
//	//find contours of filtered image using openCV findContours function
//	findContours(temp, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
//	//use moments method to find our filtered object
//	double refArea = 0;
//	bool objectFound = false;
//	if (hierarchy.size() > 0) {
//		int numObjects = hierarchy.size();
//		//if number of objects greater than MAX_NUM_OBJECTS we have a noisy filter
//		if (numObjects < MAX_NUM_OBJECTS) {
//			for (int index = 0; index >= 0; index = hierarchy[index][0]) {
//
//				Moments moment = moments((cv::Mat)contours[index]);
//				double area = moment.m00;
//
//				//if the area is less than 20 px by 20px then it is probably just noise
//				//if the area is the same as the 3/2 of the image size, probably just a bad filter
//				//we only want the object with the largest area so we safe a reference area each
//				//iteration and compare it to the area in the next iteration.
//				if (area > MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea) {
//					x = moment.m10 / area;
//					y = moment.m01 / area;
//					objectFound = true;
//					refArea = area;
//				}
//				else objectFound = false;
//
//
//			}
//			//let user know you found an object
//			if (objectFound == true) {
//				putText(cameraFeed, "Tracking Object", Point(0, 50), 2, 1, Scalar(0, 255, 0), 2);
//				//draw object location on screen
//				drawObject(x, y, cameraFeed);
//			}
//
//		}
//		else putText(cameraFeed, "TOO MUCH NOISE! ADJUST FILTER", Point(0, 50), 1, 2, Scalar(0, 0, 255), 2);
//	}
//}
//
//
//
//int main(int argc, char** argv)
//{
//
//    // Load image
//
//	Mat frame;
//	VideoCapture cap(0);
//	while (waitKey(1) < 0)
//	{
//		cap >> frame;
//		if (frame.empty())
//		{
//			break;
//		}
//		Mat HSV;
//		//x and y values for the location of the object
//		int x = 0, y = 0;
//		cvtColor(frame, HSV, COLOR_BGR2HSV);
//		createTrackbars();
//		
//		//threshold matrix
//		Mat threshold;
//		inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);
//		morphOps(threshold);
//		trackFilteredObject(x, y, threshold, frame);
//		//threshold(frame, dst, 0, 255, THRESH_BINARY);
//		imshow("video", threshold);
//		imshow("my frame", frame);
//		imshow("frame", HSV);
//	}
//    return 0;
//}

#include <iostream>
#include <string>

#include "opencv2/objdetect/objdetect.hpp"
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "filter.h"

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