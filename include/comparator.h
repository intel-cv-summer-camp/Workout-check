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

class ComparatorTemplate
{
public:
	virtual int Compare(int left[], int top[], int right[], int bot[]) = 0;
};
class Comparator_ex1 :public ComparatorTemplate
{
private:
	int left_etalon[115], top_etalon[115], right_etalon[115], bot_etalon[115];
public:
	// Пустой конструктор, чтобы был.
	Comparator_ex1();
	// Для сравнения получаю списки координат задедектированных прямоугольничков.
	// НЕ сравниваю отдельные кадры в режиме онлайн.
	// Сначала запись видео, потом сравнение полных данных.
	// left - список int координат x левого края прямоугольников и т.д.
	int Compare(int left[], int top[], int right[], int bot[]);
};