#include "comparator.h"

using namespace std;

int Comparator_ex1::Compare(int left[], int top[], int right[], int bot[])
{
	int errorcount = 0;
	int scale_etalon = right_etalon[0] - left_etalon[0];
	int scale = right[0] - left[0];
	double error = 0.1;
	for (int i = 0; i < 115; i++)
	{
		double width_etalon = (double)(right_etalon[i] - left_etalon[i])/scale_etalon;
		double width = (double)(right[i] - left[i])/scale;
		if ((width_etalon / width > 1.0 + error) || (width_etalon / width < 1.0 - error))
			errorcount++;
	}
	return errorcount;
}
int Comparator_ex2::Compare(int left[], int top[], int right[], int bot[])
{
	int errorcount = 0;
	int scale_etalon = bot_etalon[0] - top_etalon[0];
	int scale = bot[0] - top[0];
	double error = 0.1;
	for (int i = 0; i < 389; i++)
	{
		double height_etalon = (double)(bot_etalon[i] - top_etalon[i]) / scale_etalon;
		double height = (double)(bot[i] - top[i]) / scale;
		if ((height_etalon / height > 1.0 + error) || (height_etalon / height < 1.0 - error))
			errorcount++;
	}
	return errorcount;
}

int Comparator_ex3::Compare(int left[], int top[], int right[], int bot[])
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

Comparator_ex1::Comparator_ex1()
{
	string line;
	ifstream myfile("./../../Workout-check/execises/ex_1_left-right.txt");
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

Comparator_ex2::Comparator_ex2()
{
	string line;
	ifstream myfile("./../../Workout-check/execises/ex_2_up-down.txt");
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

Comparator_ex3::Comparator_ex3()
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

