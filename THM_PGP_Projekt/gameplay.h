#pragma once
struct gameplayData {
	int movecnt;
	int scrollObjects[SCROLLX][HEIGHT] = { 0 };
	unsigned int score = 0;
};
gameplayData gpd;

struct timerG {
	clock_t before;
	clock_t diff;
	u_int obstacleTimer;
	u_int obstacleTime = 30;
};
timerG timer1;

/* scrollObjectsMovement
   perform left shift (x) of all objects
*/
void scrollObjectsMovement() {
	for (int i = 1; i < SCROLLX; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			gpd.scrollObjects[i-1][j] = gpd.scrollObjects[i][j];
		}
	}
	// fill new y line with emptyness
	for (int i = 0; i < HEIGHT; i++) {
		gpd.scrollObjects[SCROLLX - 1][i] = 0;
	}
}

/* drawToScrollobjectsFilled
   draw object types to scrollobjects
   drawToScrollobjectsFilled(fromX, fromY, toX, toY, type);
*/
void drawToScrollobjectsFilled(int x1, int y1, int x2, int y2, int type) {
	if (x1 > x2)std::swap(x1, x2);
	if (y1 > y2)std::swap(y1, y2);
	assert(y1 <= HEIGHT);
	assert(y2 <= HEIGHT);
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j < y2; j++) {
			if (i >= 0) {
				gpd.scrollObjects[i][j] = type;
			}
		}
	}
}

/* scrollobjectsToPixelBuffer
   put every single element of scrollobjects in the Console Buffer
*/
void scrollobjectsToPixelBuffer() {
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if(gpd.scrollObjects[i][j] == 1)
				putPixel(i, j, ' ', BACKGROUND_RED);
		}
	}
}

void drawScore() {

}

void game() {
	gpd.movecnt++;
	gpd.score++;
	if (gpd.movecnt == 30) {
		gpd.movecnt = 0;
		runObstacleGen();
		for (int i = 0; i < HINHEIGHT; i++) {
			if (oO[i].scX1 != oO[i].scX2) {
				drawToScrollobjectsFilled(oO[i].scX1, oO[i].scY, oO[i].scX2, oO[i].scY-1, 1);
			}
		}

	}
	scrollobjectsToPixelBuffer();
	scrollObjectsMovement();
	drawUInt(0, 0, gpd.score);
	rasterize(screenInfo.bufferHandle, screenInfo.bufferSize,
		screenInfo.bufferCoord, screenInfo.writeCoord);

	timer1.before = clock();
}

void gameTimer() {
	timer1.before = clock();
	gpd.movecnt = 29;
	while (true) {
		timer1.diff = clock() - timer1.before;
		if (timer1.diff >= 50) {
			
			game();
		}

	}
}