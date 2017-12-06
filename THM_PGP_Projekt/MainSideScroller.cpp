
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <Windows.h>
#include <stdlib.h>
#include "scorelist.h"
#include <dos.h>
#include <time.h>
#define WIDTH 70
#define HEIGHT 15

//
struct tile {
	bool isPlayer = false;
	bool isWall = false;;
};

//Zeichnet das "Pixelarray" und begrenzt die zeit 
double draw(tile pixel[][HEIGHT]) {

	clock_t e;
	clock_t s = clock() / CLOCKS_PER_SEC;
	system("cls");
	for (int x = 0; x < HEIGHT; x++) {
		for (int y = 0; y < WIDTH; y++) {
			if (pixel[y][x].isWall)putchar('#');
			else if (pixel[y][x].isPlayer)putchar('$');
			else putchar(' ');
		}

		putchar('\n');
	}

	e = clock() / CLOCKS_PER_SEC;
	double dt = (double)(s - e) * 100;
	//printf(" Draw dt : %f", dt);
	//if (dt < 9) Sleep(10 - dt);
	//printf("   %f", 10 - dt);

	return difftime(clock() / CLOCKS_PER_SEC, s);
}


int main()
{	//Spielfeld
	tile spielfeld[WIDTH][HEIGHT];

	//Initialisierung des Spielers(testweise)
	int a = 0;
	spielfeld[3][a].isPlayer = true;
	tile* pPointer = &spielfeld[3][a];
	clock_t p = clock();
	clock_t e = clock();
	while (true) {

		p = clock();
		draw(spielfeld);
		e = clock();
		double dt = (e - p);
		//Sleep(100);
		printf("%.20f", dt);
		
		a += 1;
		a %= HEIGHT;


		pPointer->isPlayer = false;
		pPointer = &spielfeld[3][a];
		pPointer->isPlayer = true;
	}

	getchar();
	return 0;

}




