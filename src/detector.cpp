#include "detector.h"

//#include <iostream>
//#include <string>
//
//#include "opencv2/objdetect/objdetect.hpp"
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui.hpp>
//
//
//
//Detector_haar::Detector_haar(CascadeClassifier face_cascade_, CascadeClassifier face_cascade_prof_)
//{
//	face_cascade = face_cascade_;
//	face_cascade_prof = face_cascade_prof_;
//}
//
//vector<DetectedObject> Detector_haar::Detect(Mat frame)
//{
//	vector<DetectedObject> faces;
//	face_cascade_prof.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//	if (faces.empty())
//	{
//		Mat dst;
//		int i = -45;
//		while (faces.empty())
//		{
//			Point2f src_center(frame.cols / 2.0F, frame.rows / 2.0F);
//			Mat rot_mat = getRotationMatrix2D(src_center, i, 1.0);
//
//			warpAffine(frame, dst, rot_mat, frame.size());
//			// Detect faces
//			face_cascade.detectMultiScale(dst, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
//			if (i == 45) i = -45;
//			i += 45;
//		}
//		return faces;
//		
//}