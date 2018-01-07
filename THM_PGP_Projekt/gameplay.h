#pragma once

#define SCORE_DIFF 5
#define SCORE_LVL1 50
#define SCORE_LVL2 100
#define SCORE_LVL3 150
#define SCORE_LVL4 200

#include "player.h"
#include <math.h>
struct gameplayData {
	int movecnt;
	int scrollObjects[SCROLLX][HEIGHT] = { 0 };
	unsigned int score = 0;
	unsigned int lvl = 1;
	unsigned int lvlScroolSpeed = 0;
	short obstacleSpace;
	short scoreDiff = 0;
	bool inGame;
	bool genObstacles = true;
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
	int dt = gpd.lvlScroolSpeed;
	for (int i = 1; i < SCROLLX; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			if (i + dt < SCROLLX) {
				gpd.scrollObjects[i][j] = gpd.scrollObjects[(int)(i + dt)][j];
			}
		}
	}
	// fill new y line with emptyness
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

/*	levelDecider
	switches level depending on actual score
*/
void levelDecider() {
	switch (gpd.score) {
	case 0:
		gpd.lvl = 1;
		gpd.lvlScroolSpeed = 1;
		gpd.obstacleSpace = 50;
		gpd.genObstacles = true;
		break;
	case SCORE_LVL1:
		gpd.lvl = 2;
		gpd.lvlScroolSpeed = 2;
		gpd.obstacleSpace = 40;
		gpd.genObstacles = true;
		break;
	case SCORE_LVL2:
		gpd.lvl = 3;
		gpd.lvlScroolSpeed = 2;
		gpd.obstacleSpace = 30;
		gpd.genObstacles = true;
		break;
	case SCORE_LVL3:
		gpd.lvl = 4;
		gpd.lvlScroolSpeed = 3;
		gpd.obstacleSpace = 25;
		gpd.genObstacles = true;
		break;
	case SCORE_LVL4:
		gpd.lvl = 5;
		gpd.lvlScroolSpeed = 5;
		gpd.obstacleSpace = 15;
		gpd.genObstacles = true;
		break;

	default:
		// Do nothing;
		break;
	}
}

/*	obstacleBreak
	stops the obstacle generation if a new level is near
*/
void obstacleBreak() {
	if (gpd.score == SCORE_LVL1 - SCORE_DIFF || gpd.score == SCORE_LVL2 - SCORE_DIFF || gpd.score == SCORE_LVL3 - SCORE_DIFF || gpd.score == SCORE_LVL4 - SCORE_DIFF) {
		gpd.genObstacles = false;
	}
}

/*	drawIngameInformation
	Draws the ingame overlay
*/
void drawIngameInformation() {
	drawUInt(0, 0, gpd.score);
	putPixel(21, 0, 'l', BACKGROUND_GREEN | FOREGROUND_BLUE);
	putPixel(22, 0, 'v', BACKGROUND_GREEN | FOREGROUND_BLUE);
	putPixel(23, 0, 'l', BACKGROUND_GREEN | FOREGROUND_BLUE);
	drawUInt(25, 0, gpd.lvl);
}

/*	game
	main game execution
*/
void game(double t) {
	gpd.movecnt++;
	gpd.scoreDiff++;
	if (gpd.scoreDiff >= 10) {
		gpd.scoreDiff = 0;
		levelDecider();
		gpd.score++;
	}
	obstacleBreak();
	if (gpd.movecnt >= gpd.obstacleSpace) {
		gpd.movecnt = 0;
		if (gpd.genObstacles == true) {
			runObstacleGen();
			for (int i = 0; i < HINHEIGHT; i++) {
				if (oO[i].scX1 != oO[i].scX2) {
					drawToScrollobjectsFilled(oO[i].scX1, oO[i].scY, oO[i].scX2, oO[i].scY - 1, 1);
				}
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
	rasterize(screenInfo.bufferHandle, screenInfo.bufferSize, screenInfo.bufferCoord, screenInfo.writeCoord);
	
	timer1.before = clock();
}

/*	gameTimer
	Continuously calls game
*/
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