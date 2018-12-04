#pragma once
#include <string>
#include "raylib.h"


class Button : Rectangle
{
private:
	//Variables
	Texture2D * spriteCells = NULL;
	int cellCount = 1;
	int buttonState = 0;

public:

	int update(); //Updates the button based on the mouse position
	void draw(); //draws the button based on its state
	Rectangle getRect();
	int getState();
	//Constructor
	Button(const std::string filename, const  int cellCount, int _x, int _y);
	Button();
	~Button();


};