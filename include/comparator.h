#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/dnn.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include "includes.h"
#include <fstream>

using namespace cv;
using namespace std;

class ComparatorTemplate1
{
public:
	virtual int Compare(int left[], int top[], int right[], int bot[]) = 0;
};
class ComparatorTemplate2
{
public:
	virtual int Compare(vector<DetectedObject> vect) = 0;
};

class Comparator_ex1 :public ComparatorTemplate1
{
private:
	int left_etalon[119], top_etalon[119], right_etalon[119], bot_etalon[119]; //119 - количество строк в файлике эталона
public:
	Comparator_ex1();
	int Compare(int left[], int top[], int right[], int bot[]);
};

class comparison_ex2 :public ComparatorTemplate2
{
	string line;
public:
	comparison_ex2();
	int Compare(vector<DetectedObject> vect);
};
class comparison_ex3 :public ComparatorTemplate2
{
	string line;
public:
	comparison_ex3();
	int Compare(vector<DetectedObject> vect);
};