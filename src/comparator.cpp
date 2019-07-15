#include "comparator.h"

using namespace std;

Comparator_ex1::Comparator_ex1()
{
	string line;
	ifstream myfile("./../../Workout-check/execises/ex_3_angles.txt");
	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile, line))
		{
			//cout << line << '\n';
			left_etalon[i] = stoi(line.substr(0, 3));
			//cout << stoi(line.substr(0,3)) << "\n";
			top_etalon[i] = stoi(line.substr(4, 3));
			right_etalon[i] = stoi(line.substr(8, 3));
			bot_etalon[i] = stoi(line.substr(12, 3));
			i++;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}
comparison_ex2::comparison_ex2()
{}
comparison_ex3::comparison_ex3()
{}

int Comparator_ex1::Compare(int left[], int top[], int right[], int bot[])
{
	int errorcount = 0;
	double alpha0_etalon = atan((double)(bot_etalon[0] - top_etalon[0]) / (right_etalon[0] - left_etalon[0]));
	double alpha0 = atan((double)(bot[0] - top[0]) / (right[0] - left[0]));
	double natural_feature = alpha0_etalon - alpha0;
	double error = M_PI/72;
	for (int i = 0; i < 119; i++)
	{
		double alpha_etalon = atan((double)(bot_etalon[i] - top_etalon[i]) / (right_etalon[i] - left_etalon[i]));
		double alpha = atan((double)(bot[i] - top[i]) / (right[i] - left[i]));
		if ((alpha_etalon - alpha - natural_feature > error) || (alpha_etalon - alpha - natural_feature < - error))
			errorcount++;
	}
	return errorcount;
}

int comparison_ex2::Compare(vector<DetectedObject> vect)
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

int comparison_ex3::Compare(vector<DetectedObject> vect)
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
