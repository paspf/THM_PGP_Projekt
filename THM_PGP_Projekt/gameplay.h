#pragma once
#include "player.h"
#include <math.h>
struct gameplayData {
	int movecnt;
	int scrollObjects[SCROLLX][HEIGHT] = { 0 };
	unsigned int score = 0;
	unsigned int lvl = 1;
	unsigned int lvlScroolSpeed = 0;
	bool inGame;
};
gameplayData gpd;

struct timerG {
	clock_t before;
	clock_t diff;
	u_int obstacleTimer;
	u_int obstacleTime = 30;
	u_int sec;
};
timerG timer1;

void resetGameplayData() {
	gpd.inGame = true;
	gpd.lvlScroolSpeed = 0;
	gpd.lvl = 1;
	gpd.score = 0;
	for (int x = 0; x < SCROLLX; x++) {
		for (int y = 0; y < HEIGHT; y++) {
			gpd.scrollObjects[x][y] = 0;
		}
	}
}

/* scrollObjectsMovement
   perform left shift (x) of all objects
*/
void scrollObjectsMovement() {
	/*for (int i = 1; i < SCROLLX; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			gpd.scrollObjects[i-1][j] = gpd.scrollObjects[i][j];
		}
	}*/
	int dt = gpd.lvlScroolSpeed;
	for (int i = 1; i < SCROLLX; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (i + dt < SCROLLX) {
				gpd.scrollObjects[i][j] = gpd.scrollObjects[(int)(i + dt)][j];
			}
		}
	}


		// fill new y line with emptyness
		/*for (int i = 0; i < HEIGHT; i++) {
			gpd.scrollObjects[SCROLLX - 1][i] = 0;
			gpd.scrollObjects[SCROLLX - 2][i] = 0;
			gpd.scrollObjects[SCROLLX - 3][i] = 0;
			gpd.scrollObjects[SCROLLX - 4][i] = 0;
			gpd.scrollObjects[SCROLLX - 5][i] = 0;
			gpd.scrollObjects[SCROLLX - 6][i] = 0;
		}*/
		for (int i = 0; i < HEIGHT; i++) {
			for (int x = 1; x <= dt; x++) {
				gpd.scrollObjects[SCROLLX - x][i] = 0;

			}
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

void levelDecider() {
	/*
	
	if (gpd.score > 100) {
		gpd.lvl = 2;
		gpd.lvlScroolSpeed = 50;
	}
	else if(gpd.score > 200) {
		gpd.lvl = 3;
		gpd.lvlScroolSpeed = 80;
	} */
	
	/*
	
	*/
	switch (gpd.score) {
	case 0:
		gpd.lvl = 1;
		gpd.lvlScroolSpeed = 1;
		break;
	case 200:
		gpd.lvl = 2;
		gpd.lvlScroolSpeed = 2;
		break;
	case 500:
		gpd.lvl = 3;
		gpd.lvlScroolSpeed = 3;
		break;
	case 900:
		gpd.lvl = 4;
		gpd.lvlScroolSpeed = 4;
		break;
	case 10000:
		gpd.lvl =54;
		gpd.lvlScroolSpeed = 100;
		break;

	default:
		// Do nothing;
		break;
	}
}

void drawScore() {

}

void drawIngameInformation() {
	drawUInt(0, 0, gpd.score);			// draw Score
	putPixel(21, 0, 'l', BACKGROUND_GREEN | FOREGROUND_BLUE);
	putPixel(22, 0, 'v', BACKGROUND_GREEN | FOREGROUND_BLUE);
	putPixel(23, 0, 'l', BACKGROUND_GREEN | FOREGROUND_BLUE);
	drawUInt(25, 0, gpd.lvl);
}

void game(double t) {
	gpd.movecnt++;
	if (gpd.score == 300) {
		gpd.movecnt = gpd.movecnt;
	}
	levelDecider();
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
	updatePlayer(t / 10000000);
	if (checkDead()) {
		gpd.inGame = false;
	}
	drawIngameInformation();
	drawPlayer();
	rasterize(screenInfo.bufferHandle, screenInfo.bufferSize,
		screenInfo.bufferCoord, screenInfo.writeCoord);
	
	timer1.before = clock();
}

void gameTimer() {
	gpd.inGame = true;
	timer1.before = clock();
	gpd.movecnt = 29;
	double t = 0;
	timer1.sec = 0;
	while (gpd.inGame) {
		timer1.diff = (clock() - timer1.before);
		t += timer1.diff;
		timer1.sec += t;
		if (t >= 10000000){
		game(t);
		t = 0;
		}
	}
}