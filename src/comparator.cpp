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
		double width_etalon = (right_etalon[i] - left_etalon[i])/scale_etalon;
		double width = (right[i] - left[i])/scale;
		if ((width_etalon / width < 1 + error) && (width_etalon / width < 1 - error))
			errorcount++;
	}
	return errorcount;
}
Comparator_ex1::Comparator_ex1()
{
	string line;
	ifstream myfile("D:/Shit/intel_summer/Workout-check/Workout-check/execises/ex_1_left-right.txt");
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
