#pragma once
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <assert.h>
#include <algorithm>

//TODO fine adjustment
#define WIDTH 80
#define HEIGHT 20

CHAR_INFO screen[WIDTH*HEIGHT];


struct screenInfo {
	COORD		bufferSize;
	COORD		bufferCoord;
	SMALL_RECT	writeCoord;
	HANDLE		bufferHandle;

}screenInfo;

void initScreen() {
	//Size of the new consoleBuffer(here reffered by screenBuffer)
	COORD bSize;

	bSize.X = WIDTH;
	bSize.Y = HEIGHT;

	//Top Left Coordinates where the date is read from
	COORD buffCoord;

	buffCoord.X = 0;
	buffCoord.Y = 0;

	//Top Left and Bottom Right corners of a clipped recttangle, where the Data is written to the consle
	SMALL_RECT write;
	write.Top = 0;
	write.Left = 0;
	write.Bottom = HEIGHT;
	write.Right = WIDTH;

	//Windows.h Referenz recommendet use
	//Creates new consoleBuffer
	HANDLE newScreenBuffer;
	newScreenBuffer = CreateConsoleScreenBuffer(
		GENERIC_READ |           // read/write access 
		GENERIC_WRITE,
		FILE_SHARE_READ |
		FILE_SHARE_WRITE,        // shared 
		NULL,                    // default security attributes 
		CONSOLE_TEXTMODE_BUFFER, // must be TEXTMODE 
		NULL);                   // reserved; must be NULL

								 //saves bufferData into prev created Struct
	screenInfo.bufferCoord = buffCoord;
	screenInfo.bufferHandle = newScreenBuffer;
	screenInfo.bufferSize = bSize;
	screenInfo.writeCoord = write;

	//Exits programm if switching to new buffer fails
	if (!SetConsoleActiveScreenBuffer(screenInfo.bufferHandle))
	{
		printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
		exit(1);
	}
}
//x and y coords in screenspace,c as set character, att as console attribute(color/intensity)
void putPixel(int x, int y, char c, WORD att) {
	assert(x >= 0);
	assert(x < WIDTH);
	assert(y >= 0);
	assert(y < HEIGHT);
	screen[x + y * WIDTH].Attributes = att;
	screen[x + y * WIDTH].Char.AsciiChar = c;
}
//sets whole screen array to col
void clearScreen(WORD col) {
	for (int x = 0; x < WIDTH; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			screen[x + y * WIDTH].Char.AsciiChar = ' ';
			screen[x + y * WIDTH].Attributes = col;

		}
	}
}
//shows screenBuffer to console
inline void rasterize(HANDLE hStdOut1, COORD bSize, COORD buffCoord, SMALL_RECT write) {
	WriteConsoleOutputA(hStdOut1, screen, bSize, buffCoord, &write);
	clearScreen(BACKGROUND_GREEN);
}
/*	drawFilledRect
	 x and y in screenspace
	 drawFilledRect(fromX, fromY, toX, toY, colour);
*/
void drawFilledRect(int x1, int y1, int x2, int y2, WORD col) {
	if (x1 > x2)std::swap(x1, x2);
	if (y1 > y2)std::swap(y1, y2);
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {

			if (i >= 0 && i < WIDTH && j >= 0 && j < HEIGHT)putPixel(i, j, ' ', col);
		}
	}
}

void drawRect(int x1, int y1, int x2, int y2, WORD col) {
	if (x1 > x2)std::swap(x1, x2);
	if (y1 > y2)std::swap(y1, y2);
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			if (i == x1 || i == x2 || j == y1 || j == y2) {
				if (i >= 0 && i < WIDTH && j >= 0 && j < HEIGHT)putPixel(i, j, ' ', col);

			}
		}
	}
}
//never to be used
int example() {
	initScreen();
	clearScreen(BACKGROUND_GREEN | FOREGROUND_RED);

	float a = 0;
	float b = 0;
	float x = 0;
	float y = 0;

	while (true) {


		if (_kbhit()) {
			char c = _getch();
			if (c == 'w')a -= .01f;
			if (c == 's')a += .01f;
			if (c == 'a')b -= .01f;
			if (c == 'd')b += .01f;

		}
		x += b;
		y += a;

		if (x > WIDTH)x = WIDTH;
		else if (x < 0)x = 0;
		if (y > HEIGHT)y = HEIGHT;
		else if (y < 0)y = 0;

		drawRect(x, y, x + 3, y + 3, BACKGROUND_RED);
		drawFilledRect(0, 0, 1, 1, BACKGROUND_BLUE);

		rasterize(screenInfo.bufferHandle, screenInfo.bufferSize,
			screenInfo.bufferCoord, screenInfo.writeCoord);
	}
}
