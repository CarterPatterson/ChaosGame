#include "button.h"
#include <string>

Button::Button(const std::string filename, const  int _cellCount, int _x, int _y)
{
	cellCount = _cellCount;
	spriteCells = new Texture2D[cellCount];
	std::string fileExtension = ".png";
	std::string filePath = "resources\\";



	for (int i = 0; i < cellCount; i++)
	{
		std::string fullPath = (filePath + filename.c_str() + std::to_string(i + 1) + fileExtension).c_str();
		spriteCells[i] = LoadTexture(fullPath.c_str());
	}
	width = spriteCells[0].width;
	height = spriteCells[0].height;
	x = _x;
	y = _y;
}

int Button::update()
{
	if ((CheckCollisionPointRec(GetMousePosition(), *this)) && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		buttonState = 1;
		return buttonState;
	}
	else if ((CheckCollisionPointRec(GetMousePosition(), *this)) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
	{
		buttonState = 2;
		return buttonState;
	}
	else
	{
		buttonState = 0;
		return buttonState;
	}
	return -1;
}

void Button::draw()
{
	if (buttonState == 1)
	{
		DrawTexture(spriteCells[1], x, y + 4, WHITE);
	}
	else
	{
		DrawTexture(spriteCells[buttonState], x, y, WHITE);
	}

}

Button::~Button()
{
	delete[] spriteCells;
};

Rectangle Button::getRect()
{
	Rectangle rect = { x, y, width, height };
	return rect;
}

int Button::getState()
{
	return buttonState;
}