
#include <stdio.h>														// bringt Ein/Ausgabefunktionen mit
#include <algorithm>
#include <ctype.h>
#include <Windows.h>													// ben�tigt um die Konsole zu leern
#include <stdlib.h>														// bringt Standardfunktionen mit
#include <time.h>														// f�r Zufallszahlen ben�tigt
#include "scorelist.h"
#include "Obstacle.h"

/*	init
	nimmt f�r das Programm
	ben�tigte initialiserungen vor
*/
void init() {
	srand(time(NULL)*clock());											// Initialisiert den Zufallszahlengenerator
	
}



int main() {
	init();
	//runObstacleGen();
	return 0;
}