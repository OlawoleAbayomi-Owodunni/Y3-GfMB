//OLAWOLE ABAYOMI-OWODUNNI
//C00278711

#include "stdio.h"
#include <random>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raylib.h"
#include "raymath.h"


#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <cmath>

void application();
void drawing();


enum P_COLS {
	NONE, pRED, pORANGE, pYELLOW, pGREEN, pBLUE, pINDIGO, pVIOLET, pWHITE, pBLACK
};

	//VARIABLES
	static const int SCREEN_WIDTH = 1280;
	static const int SCREEN_HEIGHT = 800;
	const int CANVAS_WIDTH = 600;
	const int CANVAS_HEIGHT = 600;
	const int CELL_SIZE = 25;
	const int TOTAL_COLS = CANVAS_WIDTH / CELL_SIZE;
	const int TOTAL_ROWS = CANVAS_HEIGHT / CELL_SIZE;

	int intGrid[TOTAL_ROWS][TOTAL_COLS] = {};
	Rectangle pixelGrid[TOTAL_ROWS][TOTAL_COLS] = {};

	Color transparentColor = { 0, 0, 0, 0 };

	Rectangle brushButton = { 40, 100, 100, 100 };
	Rectangle eraseButton = { 60, 100, 100, 100 };
	Rectangle shapeButton = { 40, 250, 100, 100 };
	Rectangle selctButton = { 60, 250, 100, 100 };
	Rectangle pickerButton = { 40,300,100,100 };

	int activeColour = P_COLS::pGREEN;

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

	//Game initialisation
	for (int row = 0; row < TOTAL_ROWS; row++) {
		for (int col = 0; col < TOTAL_COLS; col++) {
			intGrid[row][col] = 0;

			pixelGrid[row][col].x = 350 + (col * CELL_SIZE);
			pixelGrid[row][col].y = 100 + (row * CELL_SIZE);
			pixelGrid[row][col].width = CELL_SIZE;
			pixelGrid[row][col].height = CELL_SIZE;
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

	//input handling
	if (IsKeyPressed(KEY_ZERO)) {
		activeColour = NONE;
	}
	else if (IsKeyPressed(KEY_ONE)) {
		activeColour = pRED;
	}
	else if (IsKeyPressed(KEY_TWO)) {
		activeColour = pORANGE;
	}
	else if (IsKeyPressed(KEY_THREE)) {
		activeColour = pYELLOW;
	}
	else if (IsKeyPressed(KEY_FOUR)) {
		activeColour = pGREEN;
	}
	else if (IsKeyPressed(KEY_FIVE)) {
		activeColour = pBLUE;
	}
	else if (IsKeyPressed(KEY_SIX)) {
		activeColour = pINDIGO;
	}
	else if (IsKeyPressed(KEY_SEVEN)) {
		activeColour = pVIOLET;
	}
	else if (IsKeyPressed(KEY_EIGHT)) {
		activeColour = pWHITE;
	}
	else if (IsKeyPressed(KEY_NINE)) {
		activeColour = pBLACK;
	}

	
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		Vector2 mousePos = GetMousePosition();
		for (int r = 0; r < TOTAL_ROWS; r++) {
			for (int c = 0; c < TOTAL_COLS; c++) {
				if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
					intGrid[r][c] = activeColour;
				}
			}
		}
	}


	//grid data manipulation
	for (int row = 0; row < TOTAL_ROWS; row++) {
		for (int col = 0; col < TOTAL_COLS; col++) {

			if (intGrid[row][col] == 0) {	//transparent cells
				if (row % 2 == 0) {
					if (col % 2 == 0) DrawRectangleRec(pixelGrid[row][col], GRAY);
					else DrawRectangleRec(pixelGrid[row][col], BLACK);
				}
				else {
					if (col % 2 == 1) DrawRectangleRec(pixelGrid[row][col], GRAY);
					else DrawRectangleRec(pixelGrid[row][col], BLACK);
				}
			}

			else if (intGrid[row][col] > 0 && intGrid[row][col] < 10) { //cells that contain an active colour
				Color pixelColour;

				switch (intGrid[row][col]) {
					case 1:pixelColour = RED; break;
					case 2:pixelColour = ORANGE; break;
					case 3:pixelColour = YELLOW; break;
					case 4:pixelColour = GREEN; break;
					case 5:pixelColour = BLUE; break;
					case 6:pixelColour = DARKBLUE; break;
					case 7:pixelColour = PURPLE; break;
					case 8:pixelColour = WHITE; break;
					case 9:pixelColour = BLACK; break;
				
					default:pixelColour = MAGENTA; break;
				}

				DrawRectangleRec(pixelGrid[row][col], pixelColour);

			}
			DrawRectangleLinesEx(pixelGrid[row][col], 1.0f, WHITE);
		}
	}

	//Mode switcher
	if (GuiButton(brushButton, "")) {

	}
	GuiDrawIcon(ICON_BRUSH_CLASSIC, brushButton.x + 10, brushButton.y + 10, 5, WHITE);

	//Saving and loading
	if (GuiButton({ 1000,600,200,50 }, "-> SAVE <-")) {

	}
	if (GuiButton({ 1000,675,200,50 }, "-> LOAD <-")) {

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