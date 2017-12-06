
#include <stdio.h>
#include <algorithm>
#include <ctype.h>
#include <Windows.h>
#include <stdlib.h>
#include "scorelist.h"
#include <dos.h>
#include <time.h>
#include <sys/utime.h>
#define WIDTH 50
#define HEIGHT 15


//
struct tile {
	bool isPlayer = false;
	bool isWall = false;;
};

//Zeichnet das "Pixelarray" und begrenzt die zeit 
void draw(tile pixel[][HEIGHT]) {
	system("cls");
	for (int x = 0; x < HEIGHT; x++) {
		for (int y = 0; y < WIDTH; y++) {
			if (pixel[y][x].isWall)putchar('#');
			else if (pixel[y][x].isPlayer)putchar('$');
			else putchar('.');
		}

		putchar('\n');
	}

	
}


int main()
{	//Spielfeld
	tile spielfeld[WIDTH][HEIGHT];

	//Initialisierung des Spielers(testweise)
	float a = 0;
	spielfeld[(int)a][3].isPlayer = true;
	tile* pPointer = &spielfeld[(int)a][3];
	
	
	unsigned long deltastack = 0;
	float average;
	int samples = 0;
	
	while (true) {

		unsigned long start = GetTickCount();
		

		draw(spielfeld);
		
		a += 3;
		if (a >= WIDTH)a = 0;


		pPointer->isPlayer = false;
		pPointer = &spielfeld[(int)std::floor(a)][3];
		pPointer->isPlayer = true;

		unsigned long end = GetTickCount() - start;
		deltastack += end;
		if (samples++ == 10) {
			average = (float)deltastack / 10.0f;
			deltastack = 0;
			samples = 0;
			printf("%.7fs", average/1000);
			//Sleep(1000);
		}
		
		
	}

	getchar();
	return 0;

}




