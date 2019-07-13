#pragma once

#include "includes.h"
#include <fstream>

using namespace cv;
using namespace std;

class ComparatorTemplate
{
public:
	virtual int Compare(int left, int top, int right, int bot) = 0;
};

class comparison :public ComparatorTemplate
{
	string line;
public:
	comparison();
	int Compare(int left, int top, int right, int bot);
};