
#define SCROLLX 100														// width of the scrollObjects Array

#include <stdio.h>														// bringt Ein/Ausgabefunktionen mit
#include <algorithm>
#include <ctype.h>
#include <Windows.h>													// ben�tigt um die Konsole zu leern
#include <stdlib.h>														// bringt Standardfunktionen mit
#include <time.h>														// f�r Zufallszahlen ben�tigt
#include "graphics.h"
#include "scorelist.h"
#include "Obstacle.h"
#include "gameplay.h"

/*	init
	nimmt f�r das Programm
	ben�tigte initialiserungen vor
*/
void init() {
	srand(time(NULL)*clock());											// Initialisiert den Zufallszahlengenerator
	initScreen();
	clearScreen(BACKGROUND_GREEN | FOREGROUND_RED);
	
}



int main() {
	init();
	//example();
	//game();
	//gMovement();
	//runObstacleGen();
	gameTimer();
	_getch();
	return 0;
}