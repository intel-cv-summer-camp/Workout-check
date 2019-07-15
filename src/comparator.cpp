#include "comparator.h"

comparison::comparison()
{}

int comparison::Compare_ex_3(vector<DetectedObject> vect)
{
	int o=0;
	int prev = 0;
	int min = 0;
	int min1 = 0;
	int beg = 0;
	for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
	{
		int line = sqrt(((int)((*i).Right) - (int)((*i).Left))*((int)((*i).Right) - (int)((*i).Left)) + ((int)((*i).Bottom) - (int)((*i).Top))*((int)((*i).Bottom) - (int)((*i).Top)));
		if (line > prev)
			o++;
		else if (line < prev)
			o--;
		prev = line;
		if (beg == 0)
		{
			if (min > o && o < 0)
				min = o;
			if (abs(min - o) > 3 && o < 0)
				beg += line;
		}
		else
			if (min1 > o && o < 0)
				min1 = o;
	}
	return abs(min - min1);
}

int comparison::Compare_ex_2(vector<DetectedObject> vect)
{
	int correct = 0;
	int left_prev = 0;
	int right_prev = 0;
	int top_prev = 0;
	int bottom_prev = 0;
	for (vector<DetectedObject>::iterator i = vect.begin(); i != vect.end(); ++i)
	{
		if (abs(left_prev - (int)((*i).Left)) < 10 && abs(right_prev - (int)((*i).Right)) < 10 || abs(top_prev - (int)((*i).Top)) > 0 && abs(bottom_prev - (int)((*i).Bottom)) > 0)
			correct++;
		else correct = 0;
		left_prev = (int)((*i).Left); right_prev = (int)((*i).Right); top_prev = (int)((*i).Top); bottom_prev = (int)((*i).Bottom);
	}
	return correct;
}