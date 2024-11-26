//OLAWOLE ABAYOMI-OWODUNNI
//C00278711

#include <iostream>
#include "stdio.h"
#include <random>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "raylib.h"
#include "raymath.h"


#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

#include <cmath>
#include <vector>

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
	int enumWheel[3][3] = {	{pRED, pORANGE, pYELLOW },
							{pGREEN, pBLUE, pINDIGO},
							{pVIOLET, pWHITE, pBLACK} };
	Color colourWheel[3][3] = {	{RED, ORANGE, YELLOW },
							{GREEN, BLUE, DARKBLUE},
							{PURPLE, WHITE, BLACK} };
	

	Rectangle brushButton = { 40, 100, 100, 100 };
	Rectangle eraseButton = { 160, 100, 100, 100 };
	Rectangle shapeButton = { 40, 250, 100, 100 };
	Rectangle selctButton = { 160, 250, 100, 100 };
	Rectangle pickerButton = { 40,400,100,100 };

	int activeColour = P_COLS::pRED;
	int lastColour = activeColour;
	Color showColour = RED;

	int startC = 0;
	int startR = 0;
	int endC = 0;
	int endR = 0;

	bool canDraw = true;
	bool canPick = false;
	bool isRectTool = false;
	bool isCursorTool = false;

	bool hasCopied = false;
	bool hasPasted = false;
	int rows = 0;
	int cols = 0;
	int tempArr[100][100];

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
	if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		if (canDraw) {	//drawing functionality
			Vector2 mousePos = GetMousePosition();
			for (int r = 0; r < TOTAL_ROWS; r++) {
				for (int c = 0; c < TOTAL_COLS; c++) {
					if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
						intGrid[r][c] = activeColour;
					}
				}
			}
		}

		else if (canPick) {	//colour picking functionality
			Vector2 mousePos = GetMousePosition();
			for (int r = 0; r < TOTAL_ROWS; r++) {
				for (int c = 0; c < TOTAL_COLS; c++) {
					if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
						switch (intGrid[r][c]) {
						case 0:
							activeColour = NONE;
							showColour = GRAY;
							break;
						case 1:
							activeColour = pRED;
							showColour = RED;
							break;
						case 2:
							activeColour = pORANGE;
							showColour = ORANGE;
							break;
						case 3:
							activeColour = pYELLOW;
							showColour = YELLOW;
							break;
						case 4:
							activeColour = pGREEN;
							showColour = GREEN;
							break;
						case 5:
							activeColour = pBLUE;
							showColour = BLUE;
							break;
						case 6:
							activeColour = pINDIGO;
							showColour = DARKBLUE;
							break;
						case 7:
							activeColour = pVIOLET;
							showColour = PURPLE;
							break;
						case 8:
							activeColour = pWHITE;
							showColour = WHITE;
							break;
						case 9:
							activeColour = pBLACK;
							showColour = BLACK;
							break;
						}
					}
					lastColour = activeColour;
				}
			}
		}
	}

	if (isRectTool) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			startR = 0;
			startC = 0;
			Vector2 mousePos = GetMousePosition();
			for (int r = 0; r < TOTAL_ROWS; r++) {
				for (int c = 0; c < TOTAL_COLS; c++) {
					if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
						startR = r;
						startC = c;
					}
				}
			}

		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();
			for (int r = 0; r < TOTAL_ROWS; r++) {
				for (int c = 0; c < TOTAL_COLS; c++) {
					if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
						endR = r;
						endC = c;
						for (int r = startR; r <= endR; r++) {
							for (int c = startC; c <= endC; c++) {
								intGrid[r][c] = activeColour;
							}
						}
						break;
					}
				}
			}
		}
	}


	if (isCursorTool) {
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			startR = 0;
			startC = 0;
			Vector2 mousePos = GetMousePosition();
			for (int r = 0; r < TOTAL_ROWS; r++) {
				for (int c = 0; c < TOTAL_COLS; c++) {
					if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
						startR = r;
						startC = c;
					}
				}
			}

		}

		if (IsKeyPressed(KEY_C)) {
			hasCopied = true;
			hasPasted = false;
		}
		if (IsKeyPressed(KEY_V)) {
			hasPasted = true;
			hasCopied = false;

			for (int r = startR, i = 0; r <= startR + rows; r++, i++) {
				for (int c = startC, j = 0; c <= startC + cols; c++, j++) {
					intGrid[r][c] = tempArr[i][j];
				}
			}
		}


		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			Vector2 mousePos = GetMousePosition();
			for (int r = 0; r < TOTAL_ROWS; r++) {
				for (int c = 0; c < TOTAL_COLS; c++) {
					if (CheckCollisionPointRec(mousePos, pixelGrid[r][c])) {
						endR = r;
						endC = c;

						if (!hasCopied) {
							rows = endR - startR;
							cols = endC - startC;
						}

						for (int i = 0, r = startR; r <= endR; r++, i++) {
							for (int j = 0, c = startC; c <= endC; c++, j++) {
								tempArr[i][j] = intGrid[r][c];
							}
						}

						break;
					}
				}
			}
		}


	}

	//colour palette logic
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Rectangle button = { 1010 + (j * 60),300 + (i * 60),50,50 };
			if (GuiButton(button, "")) {
				activeColour = enumWheel[i][j];
				lastColour = activeColour;
				showColour = colourWheel[i][j];
			}
			DrawRectangleRec(button, colourWheel[i][j]);
			DrawRectangleLinesEx(button, 1.0f, WHITE);
		}
	}
	DrawRectangle(1050, 200, 100, 50, showColour);
	DrawRectangleLinesEx({1050,200,100,50}, 1.0f, WHITE);

	switch (activeColour) {
		case NONE:showColour = GRAY; break;
		case pRED:showColour = RED; break;
		case pORANGE:showColour = ORANGE; break;
		case pYELLOW:showColour = YELLOW; break;
		case pGREEN:showColour = GREEN; break;
		case pBLUE:showColour = BLUE; break;
		case pINDIGO:showColour = DARKBLUE; break;
		case pVIOLET:showColour = PURPLE; break;
		case pWHITE:showColour = WHITE; break;
		case pBLACK:showColour = BLACK; break;
	}

	//grid data manipulation
	for (int row = 0; row < TOTAL_ROWS; row++) {
		for (int col = 0; col < TOTAL_COLS; col++) {

			if (intGrid[row][col] == 0) {	//transparent cells
				if (row % 2 == 0) {
					if (col % 2 == 0) DrawRectangleRec(pixelGrid[row][col], GRAY);
					else DrawRectangleRec(pixelGrid[row][col], WHITE);
				}
				else {
					if (col % 2 == 1) DrawRectangleRec(pixelGrid[row][col], GRAY);
					else DrawRectangleRec(pixelGrid[row][col], WHITE);
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
			DrawRectangleLinesEx(pixelGrid[row][col], 1.0f, BLACK);
		}
	}

	//Mode switcher
	if (GuiButton(brushButton, "")) {
		canDraw = true;
		isRectTool = false;
		canPick = false;
		isCursorTool = false;
		activeColour = lastColour;
	}
	GuiDrawIcon(ICON_BRUSH_CLASSIC, brushButton.x + 10, brushButton.y + 10, 5, WHITE);

	if (GuiButton(eraseButton, "")) {
		canDraw = true;
		isRectTool = false;
		canPick = false;
		isCursorTool = false;
		activeColour = NONE;
	}
	GuiDrawIcon(ICON_CROSS, eraseButton.x + 10, eraseButton.y + 10, 5, WHITE);

	if (GuiButton(selctButton, "")) {
		isCursorTool = true;
		canDraw = false;
		isRectTool = false;
		canPick = false;
		
		hasCopied = false;
		hasPasted = false;
	}
	GuiDrawIcon(ICON_CURSOR_CLASSIC, selctButton.x + 10, selctButton.y + 10, 5, WHITE);

	if (GuiButton(shapeButton, "")) {
		isRectTool = true;
		canPick = false;
		canDraw = false;
		isCursorTool = false;
	}
	GuiDrawIcon(ICON_BOX, shapeButton.x + 10, shapeButton.y + 10, 5, WHITE);

	if (GuiButton(pickerButton, "")) {
		canPick = true;
		canDraw = false;
		isRectTool = false;
		isCursorTool = false;
	}
	GuiDrawIcon(ICON_COLOR_PICKER, pickerButton.x + 10, pickerButton.y + 10, 5, WHITE);


	//Saving and loading
	if (GuiButton({ 1000,600,200,50 }, "-> SAVE <-")) {
		FILE* file = fopen("imgData.bin", "wb");
		if (file != NULL) fwrite(intGrid, sizeof(int), TOTAL_ROWS * TOTAL_COLS, file);
		else printf("error opening a file to write the data on\n");
		fclose(file);
	}

	if (GuiButton({ 1000,675,200,50 }, "-> LOAD <-")) {
		FILE* file = fopen("imgData.bin", "rb");
		if (file == NULL) {
			printf("File to be read is not found...\n");
			return;
		}
		
		size_t elementsRead = fread(intGrid, sizeof(int), TOTAL_ROWS * TOTAL_COLS, file);
		if (elementsRead != TOTAL_ROWS * TOTAL_COLS) printf("Error reading data from file\n");
		fclose(file);
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