#pragma once

#include "includes.h"

#define MAX_NUMBER_OF_ITEMS 2

class GUI
{
public:
	GUI();	
	GUI(int width, int height);

	void Run();	
	void MoveRight();
	void MoveLeft();
	int GetPressedItem() { return selectedItemIndex; }

private:
	int selectedItemIndex;
	bool isMenu;
	int width;
	int height;
	sf::Font font;
	sf::Text button[MAX_NUMBER_OF_ITEMS];
};


