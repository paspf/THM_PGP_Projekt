
#define SCROLLX 100														// width of the scrollObjects Array

#include <stdio.h>														
#include <algorithm>
#include <ctype.h>
#include <Windows.h>													
#include <stdlib.h>														
#include <time.h>														
#include "graphics.h"
#include "scorelist.h"
#include "Obstacle.h"
#include "gameplay.h"
#include "player.h"

/*	init
	initializes all necessary values
*/
void init() {
	srand(time(NULL)*clock());											// initialize random generator
	initScreen();                                                       // initialize Screen
	clearScreen(BACKGROUND_GREEN | FOREGROUND_RED);
	initPlayer();                                                       // initialize Player
	resetGameplayData();                                                // initialize gameplayData struct
}



int main() {
	bool inGame = true;
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);					//for late on/output ( handle is changed in graphics.h
	printf("Beliebigen Knopf druecken zum starten, Leertaste zum springen!");
	_getch();
	init();
	while (inGame) {													// main gameloop
		gameTimer();
		SetConsoleActiveScreenBuffer(stdHandle);						// reset console to standard handle
		saveScoreToFile(gpd.score);
		showScorelist();
		printf("\nNochmal spielen?(y/n)");
		char c = _getch();
		if (c == 'n')inGame = false;
		init();
	}
	return 0;
}