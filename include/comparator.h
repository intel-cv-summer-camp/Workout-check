#pragma once

#include "includes.h"
#include <fstream>

using namespace cv;
using namespace std;

class ComparatorTemplate
{
public:
	virtual int Compare_ex_3(vector<DetectedObject> vect) = 0;
	virtual int Compare_ex_2(vector<DetectedObject>) = 0;
};

class comparison :public ComparatorTemplate
{
	string line;
public:
	comparison();
	int Compare_ex_3(vector<DetectedObject> vect);
	int Compare_ex_2(vector<DetectedObject>);
};