#pragma once

#define hinwidth 15
#define hinheight 5

struct obstacleDat {
	int xp = 0;															// x position, obstacle startposition
	int xw = 0;															// x width, obstacle width
	int scY = 0;
	int scX1 = 0;
	int scX2 = 0;
};
obstacleDat *oO;														// create dynamic array obstacleObjekt

void obstacle();
void hinClr();
void hinFree();
void obstacleHandler(int);


void runObstacleGen() {
//	system("cls");														// systemcall to clean up cmd
	oO = (obstacleDat*)malloc(hinheight * sizeof(obstacleDat));					// allocate memory for ebery obstacle level
	hinClr();															// ensure all values are 0
	obstacle();
	//hinFree();
}

/*	randomNum
generate random number
between 0 and commited scope
*/
int randomNum(int scope) {
	int ranNumber = rand() % scope;										// random number between 0 and scope
	return ranNumber;
}

/*	obstacle
start obstacle generator
*/
void obstacle() {

	oO[0].xw = randomNum(hinwidth);										// generate width for the lowest obstacle level
	oO[0].xp = 0;														// fist x position has to be 0										
	obstacleHandler(0);													// generate rest of obstacle levels

	int obstacleX = 0;
	int obstacleY = 0;
	int width = 0;

	for (int i = 0; i < hinheight; i++) {
		oO[i].scX1 = WIDTH - hinwidth + oO[i].xp;
		oO[i].scX2 = WIDTH - hinwidth + oO[i].xp + oO[i].xw;
		oO[i].scY = HEIGHT - i;
	}
	/*
		for (int i = hinheight - 1; i >= 0; i--) {
		for (int j = 0; j < hinwidth; j++) {
			if (j >= oO[i].xp) {
				if (oO[i].xw > width) {
					//printf("G");
					oO[i].scY = HEIGHT - i;
					oO[i].scX = WIDTH - j;
					//drawRect(obstacleX, obstacleY, obstacleX-1, obstacleY-1, BACKGROUND_RED);
					width++;
				}
				else {
					//printf(".");
				}
			}
			else {
				//printf(".");
			}
		}
		width = 0;
		printf("\n");
	}
	*/

}

/*	hinClr
clear up all the old obstacles
to avoid conflicts
*/
void hinClr() {
	for (int i = 0; i < hinheight; i++) {
		oO[i].xp = 0;
		oO[i].xw = 0;
	}
}

/*	hinFree
release for memory allocated to obstaclegenerator
*/
void hinFree() {
	free(oO);
}

/*	obstacleHandler
generate recursive new obstacles,
until the coplete obstacle field is filled
with obstacles or emptyness
*/
void obstacleHandler(int hIs) {
	int hNext = hIs + 1;
	if (oO[hIs].xw != 0) {												// last level obstacle width is not 0
		oO[hNext].xw = randomNum(oO[hIs].xw);							// generate new level obstacle width, smaller than width of the last level
		if (oO[hNext].xw != 0) {										// new level obstacle width is bigger than 0
			int tmp = oO[hIs].xw - oO[hNext].xw;						// old obstacle width - new obstacle width
			if (tmp == 0) {												// new obstacle width == old obstacle width
				oO[hNext].xp = oO[hIs].xp;								// startpoint of new obstacle = startpoint of old obstacle
			}
			else {														// width of old and new obstacle is not similar
				oO[hNext].xp = randomNum(tmp);							// random new startpoint hast to be smaller than the difference between old width and new width
				oO[hNext].xp = oO[hNext].xp + oO[hIs].xp;				// new startpoint + old startpoint, the new obstacle is now above the old obstacle
			}
		}
	}
	if (hNext < hinheight - 1) {
		obstacleHandler(hNext);											// generate next obstacle level
	}
}