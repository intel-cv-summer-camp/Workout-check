#include "comparator.h"

comparison::comparison()
{
	/*ifstream myfile("C:/Users/Валентин/Desktop/Workout-check/execises/ex_2_up-down.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}
	else cout << "Unable to open file";*/
}

int comparison:: Compare(int left, int top, int right, int bot)
{
	int nowrong = 0;
	stringstream str;
	string s;
	str << left << "\t" << right << "\t" << top << "\t" << bot << endl;
	str >> s;
	ifstream myfile("C:/Users/Валентин/Desktop/Workout-check/execises/ex_2_up-down.txt");
	if (myfile.is_open())
	{
		int i = 0;
		while (getline(myfile, line))
		{
			if (s == line)
			{
				nowrong++;
			}
			i++;
		}
		myfile.close();
	}
	else cout << "Unable to open file";
	return nowrong;
}