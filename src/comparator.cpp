#include "comparator.h"


using namespace std;

int Comparator_ex1::Compare(int* left[], int* top[], int* right[], int* bot[])
{
	int errorcount = 0;
	return errorcount;
}
Comparator_ex1::Comparator_ex1()
{
	string line;
	ifstream myfile("D:/Shit/intel_summer/Workout-check/Workout-check/execises/ex_1_left-right.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";
}
