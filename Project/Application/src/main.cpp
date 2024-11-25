//OLAWOLE ABAYOMI-OWODUNNI
//C00278711

#include "stdio.h"
#include <random>

#include "raylib.h"
#include "raymath.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <cmath>

void application();
void drawing();

	//VARIABLES
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 800;
	const int CANVAS_WIDTH = 600;
	const int CANVAS_HEIGHT = 600;
	const int CELL_SIZE = 25;
	const int TOTAL_COLS = CANVAS_WIDTH / CELL_SIZE;
	const int TOTAL_ROWS = CANVAS_HEIGHT / CELL_SIZE;
	int transGrid[TOTAL_ROWS][TOTAL_COLS] = {};
	int pixelGrid[TOTAL_ROWS][TOTAL_COLS] = {};

	// Load a texture from the resources directory
	Texture wabbit = LoadTexture("wabbit_alpha.png");

int main ()
{
	// Tell the window to use vysnc and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Olawole's Pixel Editor");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");

	for (int row = 0; row < TOTAL_ROWS; row++) {
		for (int col = 0; col < TOTAL_COLS; col++) {
			transGrid[row][col] = 0;
			pixelGrid[row][col] = 0;
			
			int x = col * CELL_SIZE;
			int y = row * CELL_SIZE;

			if (row % 2 == 0) DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, GRAY);
			else DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, WHITE);
		}
	}


	// game loop
	while (!WindowShouldClose())		// run the loop untill the user presses ESCAPE or presses the Close button on the window
	{
		application();
;		drawing();
	}

	// cleanup
	// unload our texture so it can be cleaned up
	UnloadTexture(wabbit);

	// destory the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

void application() {
	// drawing
	BeginDrawing();

	// Setup the backbuffer for drawing (clear color and depth buffers)
	ClearBackground(BLACK);

	for (int row = 0; row < TOTAL_ROWS; row++) {
		for (int col = 0; col < TOTAL_COLS; col++) {

			int x = 350 + (col * CELL_SIZE);
			int y = 100 + (row * CELL_SIZE);

			if (row % 2 == 0) {
				if (col % 2 == 0) DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, GRAY);
				else DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, BLACK);
			}
			else {
				if (col % 2 == 1) DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, GRAY);
				else DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, BLACK);
			}
		}
	}
}

void drawing() {

	// draw some text using the default font
	DrawText("Pixel Editor", 550, 50, 30, WHITE);

	// draw our texture to the screen
	DrawTexture(wabbit, 400, 200, BLACK);

	// end the frame and get ready for the next one  (display frame, poll input, etc...)
	EndDrawing();

}