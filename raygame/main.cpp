/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "Button.h"
#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <string>

class Point {
public:
	Vector2 pos;
	Color color;

	Point() {}
	Point(Vector2 _pos, Color _color) {
		pos = _pos;
		color = _color;
	}
	~Point() {}

	void draw() {
		DrawPixelV(pos, color);
	}
};

Vector2 Lerp(Vector2 start, Vector2 end, float percent) { //My linear interpolation function
	return { start.x + percent * (end.x - start.x), start.y + percent * (end.y - start.y) };
}


Color randColor() { //Select random color from given list
	Color c;
	
	int r = GetRandomValue(0, 20);

	switch (r) {
	case 0:
		c = LIGHTGRAY;
		break;
	case 1:
		c = GRAY;
		break;
	case 2:
		c = DARKGRAY;
		break;
	case 3:
		c = YELLOW;
		break;
	case 4:
		c = GOLD;
		break;
	case 5:
		c = ORANGE;
		break;
	case 6:
		c = PINK;
		break;
	case 7:
		c = RED;
		break;
	case 8:
		c = MAROON;
		break;
	case 9:
		c = GREEN;
		break;
	case 10:
		c = LIME;
		break;
	case 11:
		c = DARKGREEN;
		break;
	case 12:
		c = SKYBLUE;
		break;
	case 13:
		c = BLUE;
		break;
	case 14:
		c = DARKBLUE;
		break;
	case 15:
		c = PURPLE;
		break;
	case 16:
		c = VIOLET;
		break;
	case 17:
		c = DARKPURPLE;
		break;
	case 18:
		c = BEIGE;
		break;
	case 19:
		c = BROWN;
		break;
	case 20:
		c = DARKBROWN;
		break;
	}
	return c;
}


int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------

	srand(time(NULL));

	bool firstRun = true;

	int STATE = 0;

	int screenWidth, screenHeight;

	int pointsPerFrame = 1;
	float lerpPercent = 0.5f;

	std::cout << "Window Width: ";
	std::cin >> screenWidth;
	std::cout << "\nWindow Height: ";
	std::cin >> screenHeight;

	std::vector<Point> masterPoints;
	std::vector<Point> points;

	if (screenWidth < 299) {
		screenWidth = 300;
	}

	if (screenHeight < 299) {
		screenHeight = 300;
	}

	InitWindow(screenWidth, screenHeight, "raylib [core] example - Chaos Game");

	Rectangle screenRect = {0, 0, screenWidth, screenHeight};
	Rectangle playRect = {0, 0, screenWidth - 100, screenHeight};
	Rectangle UIRect = {playRect.width, 0, screenWidth - playRect.width, screenHeight};

	Button buttons[2] = {
		{"blue_button", 2, screenWidth - 98, 0 },
		{"red_button", 2, screenWidth - 49, 0 }
	};


	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------

		for (size_t i = 0; i < 2; i++) //Simulate buttons
		{
			buttons[i].update();
		}

		if (IsKeyDown(KEY_UP)) { //Increase amount of pixels generated per frame
			pointsPerFrame++;
		}

		if (IsKeyDown(KEY_DOWN) && pointsPerFrame > 1) { //Decrease that amount
			pointsPerFrame--;
		}

		if (IsKeyDown(KEY_RIGHT)) { //Increase percentage of lerp between last point and chosen master point
			lerpPercent += 0.01f;
		}

		if (IsKeyDown(KEY_LEFT) && lerpPercent > 0.1f) { //Decrease that amount
			lerpPercent -= 0.01f;
		}

		if (buttons[0].getState() == 2 && masterPoints.size() > 0) { //Change state to go mode
			STATE = 1;
		}

		if (buttons[1].getState() == 2 && masterPoints.size() > 0) { //Change state to halt and clear vectors
			STATE = 0;
			masterPoints.clear();
			points.clear();
			firstRun = true;
		}

		switch (STATE) { //State machine
		case 0: {
			if (CheckCollisionPointRec(GetMousePosition(), playRect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				masterPoints.push_back(Point({ (float)GetMouseX(), (float)GetMouseY() }, RED));
			}		
		}
				break;
		case 1: {
			for (int i = 0; i < pointsPerFrame; i++) {
				Vector2 rPos;
				size_t r = GetRandomValue(0, INT_MAX) % masterPoints.size();

				if (firstRun) {
					rPos = { (float)GetRandomValue(0, screenWidth), (float)GetRandomValue(0, screenHeight) };
					firstRun = false;
				} else {
					rPos = Lerp(points[points.size() - 1].pos, masterPoints[r].pos, lerpPercent);
				}

				points.push_back(Point(rPos, randColor()));
			}
			break;
		}
	}




		//----------------------------------------------------------------------------------

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(BLACK);



		for (size_t i = 0; i < points.size(); i++) {
			points[i].draw();
		}

		for (size_t i = 0; i < masterPoints.size(); i++) {
			masterPoints[i].color = randColor();
			masterPoints[i].draw();
		}

		DrawRectangleRec(UIRect, LIGHTGRAY);

		for (size_t i = 0; i < 2; i++) //Draw buttons
		{
			buttons[i].draw();
		}

		DrawFPS(100,100);
		DrawText(std::to_string(pointsPerFrame).c_str(), screenWidth - 95, screenHeight / 2, 55, BLACK);
		DrawText(std::to_string(lerpPercent).c_str(), screenWidth - 95, screenHeight / 2 + 50, 20, BLACK);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}