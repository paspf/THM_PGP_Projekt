#pragma once
struct gameplayData {
	int movecnt;
};
gameplayData gpd;

struct timerG {
	clock_t before;
	clock_t diff;
	u_int obstacleTimer;
	u_int obstacleTime = 30;
};
timerG timer1;

void oMovement() {
	for (int i = 0; i < hinheight; i++) {
		oO[i].scX1 -= 1;
		oO[i].scX2 -= 1;
	}

	rasterize(screenInfo.bufferHandle, screenInfo.bufferSize,
		screenInfo.bufferCoord, screenInfo.writeCoord);
}

void game() {
	gpd.movecnt++;
	if (gpd.movecnt == 30) {
		gpd.movecnt = 0;
		runObstacleGen();

	}
	oMovement();
	for (int i = 0; i < hinheight; i++) {
		if (oO[i].scX1 != oO[i].scX2) {
			drawRect(oO[i].scX1, oO[i].scY, oO[i].scX2, oO[i].scY - 1, BACKGROUND_RED);
		}
	}
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