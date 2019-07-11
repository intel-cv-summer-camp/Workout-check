#include "preparator.h"
#include "detector.h"
#include "tracker.h"
#include "comparator.h"

bool debug = true; // runtime debug flag

using namespace std;
using namespace cv;

int main()
{
	int sourceId = 0; // corresponds to what video canal we use for input, '0' is laptop webcam

	cv::Mat frame;
	cv::VideoCapture cam(sourceId);

	Data dataFromDetector;
	Data dataFromTracker;
	Data dataFromComparator;

	Detector detector;
	Tracker tracker;
	Comparator comparator;

	while (waitKey(1) < 0)
	{
		cam >> frame;
		if (frame.empty())
			break;

		dataFromDetector = detector.Detect(frame);
		dataFromTracker = tracker.Track(dataFromDetector);
		dataFromComparator = comparator.Compare(dataFromTracker);
		
		if (dataFromComparator.isGood())
		{
			cout << "Excersize done correctly" << endl;
		}
		else
		{
			cout << "Excersize done incorrectly, do it again please" << endl;
		}

		if (debug)
			imshow("WorkoutCheck", frame);
	}
	return 0;
}