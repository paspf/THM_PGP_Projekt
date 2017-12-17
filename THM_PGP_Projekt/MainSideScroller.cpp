
#include <stdio.h>														// bringt Ein/Ausgabefunktionen mit
#include <algorithm>
#include <ctype.h>
#include <Windows.h>													// benötigt um die Konsole zu leern
#include <stdlib.h>														// bringt Standardfunktionen mit
#include <time.h>														// für Zufallszahlen benötigt
#include "scorelist.h"
#include "Obstacle.h"

/*	init
	nimmt für das Programm
	benötigte initialiserungen vor
*/
void init() {
	srand(time(NULL)*clock());											// Initialisiert den Zufallszahlengenerator
	
}



int main() {
	init();
	//runObstacleGen();
	return 0;
}