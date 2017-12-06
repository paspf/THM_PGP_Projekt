#include <time.h>
#include <windows.h>
#include <stdio.h>

#define hinwidth 30
#define hinheight 5

struct hinDat {
	int xp = 0;															// x position, startposition des Hindernis
	int xw = 0;															// x width, breite des Hindernis
};
hinDat *hd;

void hindernisGen() {
	system("cls");														// Systemaufruf zum s�ubern des Fensters, teil von windows.h
	hd = (hinDat*)malloc(hinheight * sizeof(hinDat));					// reserviere Speicherplatz f�r die Hindernisebenen
	while (1) {
		hindernis();
	}
}

/*	randomNum
Generiert eine Zuf�llige Zahl
zwischen 1 und der �bergebenen Bereichsgrenze
*/
int randomNum(int bereich) {
	int ranNumber = rand() % bereich;									// Zufallszahl zwischen 0 und bereich
	return ranNumber;
}

/*	hindernisV3
initialisiert Hindernisgeneration
*/
void hindernis() {

	hd[0].xw = randomNum(hinwidth);										// generiere Hindernisbreite f�r die unterste Hindernisebene
	hd[0].xp = 0;														// erste x pos muss 0 sein											
	hindernisV3Handler(0);												// generiere die weiteren Hindernisebenen

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
	hinClr();
}

/*	hinClr
L�scht die Positionen der alten Hindernisse,
um Konflikte zu vermeiden
*/
void hinClr() {
	for (int i = 0; i < hinheight; i++) {
		hd[i].xp = 0;
		hd[i].xw = 0;
	}
}

/*	hinFree
gibt f�r den Hindernisgenerator
reservierten Speicherplatz wieder frei
*/
void hinFree() {
	free(hd);
}

/*	hindernisV3Handler
generiert rekursiv neue hindernisse,
bis das Komplette, f�r die Hindernisse freigegebene Feld
mit Hindernisse, oder Freizeichen beschrieben ist
*/
void hindernisV3Handler(int hIs) {
	int hNext = hIs + 1;
	if (hd[hIs].xw != 0) {												// alte hindernisbreite ist ungleich 0
		hd[hNext].xw = randomNum(hd[hIs].xw);							// Generiert Zahl f�r ein neues xw breites Hindernis, welches kleiner als das Hindernis in der letzten Ebene sein muss
		if (hd[hNext].xw != 0) {										// Hat der Zufallsgenerator gesagt es soll ein xw breites Hindernis generiert werden?
			int tmp = hd[hIs].xw - hd[hNext].xw;						// alte menge - neue nenge
			if (tmp == 0) {												// Das neue Hindernis ist genauso breit wie das alte
				hd[hNext].xp = hd[hIs].xp;								// 0 + alte startzahl, new und alt sind gleichgro�
			}
			else {														// Sind altes und neues Hindernis unterschiedlich breit
				hd[hNext].xp = randomNum(tmp);							// berechne neue Startzahl die kleiner ist als die Breitendifferenz zum alten Hindernis
				hd[hNext].xp = hd[hNext].xp + hd[hIs].xp;				// neue Startzahl + alte Startzahl, damit die n�chste Hindernisebene �ber der alten liegt
			}
		}
	}
	if (hNext < hinheight - 1) {
		hindernisV3Handler(hNext);										// generiere neue hindernisebene
	}
}