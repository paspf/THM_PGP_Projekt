#pragma once

#define hinwidth 30
#define hinheight 5

struct hinDat {
	int xp = 0;															// x position, startposition des Hindernis
	int xw = 0;															// x width, breite des Hindernis
};
hinDat *hd;

void obstacle();
void hinClr();
void hinFree();
void obstacleHandler(int);

/*	initObstacleGen
	initialize obstaclegenerator
*/
void runObstacleGen() {
//	system("cls");														// systemcall to clean up cmd
	hd = (hinDat*)malloc(hinheight * sizeof(hinDat));					// allocate memory for ebery obstacle level
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

	hd[0].xw = randomNum(hinwidth);										// generate width for the lowest obstacle level
	hd[0].xp = 0;														// fist x position has to be 0										
	obstacleHandler(0);													// generate rest of obstacle levels

	int width = 0;
	for (int i = hinheight - 1; i >= 0; i--) {
		for (int j = 0; j < hinwidth; j++) {
			if (j >= hd[i].xp) {
				if (hd[i].xw > width) {
					printf("G");
					width++;
				}
				else {
					printf(".");
				}
			}
			else {
				printf(".");
			}
		}
		width = 0;
		printf("\n");
	}
}

/*	hinClr
clear up all the old obstacles
to avoid conflicts
*/
void hinClr() {
	for (int i = 0; i < hinheight; i++) {
		hd[i].xp = 0;
		hd[i].xw = 0;
	}
}

/*	hinFree
release for memory allocated to obstaclegenerator
*/
void hinFree() {
	free(hd);
}

/*	obstacleHandler
generate recursive new obstacles,
until the coplete obstacle field is filled
with obstacles or emptyness
*/
void obstacleHandler(int hIs) {
	int hNext = hIs + 1;
	if (hd[hIs].xw != 0) {												// last level obstacle width is not 0
		hd[hNext].xw = randomNum(hd[hIs].xw);							// generate new level obstacle width, smaller than width of the last level
		if (hd[hNext].xw != 0) {										// new level obstacle width is bigger than 0
			int tmp = hd[hIs].xw - hd[hNext].xw;						// old obstacle width - new obstacle width
			if (tmp == 0) {												// new obstacle width == old obstacle width
				hd[hNext].xp = hd[hIs].xp;								// startpoint of new obstacle = startpoint of old obstacle
			}
			else {														// width of old and new obstacle is not similar
				hd[hNext].xp = randomNum(tmp);							// random new startpoint hast to be smaller than the difference between old width and new width
				hd[hNext].xp = hd[hNext].xp + hd[hIs].xp;				// new startpoint + old startpoint, the new obstacle is now above the old obstacle
			}
		}
	}
	if (hNext < hinheight - 1) {
		obstacleHandler(hNext);											// generate next obstacle level
	}
}