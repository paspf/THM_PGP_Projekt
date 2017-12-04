#pragma once
#define BUFFERSIZE 255
#define _MAX_NAME_LENGTH 11
//#include <stdio.h>

/*
Funktionsbeschreibung...


*/
void eingabe(char *buff) {


	int i = 0;
	//einlesen von eingabezeichen
	do {

		buff[i] = getchar();

		if (buff[i] == '\n') {
			buff[i] = '\0';
			break;
		}
		i++;
	} while (i < BUFFERSIZE - 1);

}


/*
Funktionsbeschreibung...


*/
void eingabeFixed(char *buff, int w) {

	int i = 0;												// Position im Bufferarray
	int n = 0;												// Was ist n?
	//einlesen von eingabezeichen

	do {

		buff[i] = getchar();

		if (buff[i] == '\n') {
			buff[i] = '\0';
			break;
		}
		i++;
		n++;
	} while (i < BUFFERSIZE - 1 && i < w);
	//Ist die eingabe Länger als die vorgegebene größe?!
	if (i >= w) {
		printf("ZU GROSS, NOCHMAL\n");
		char c = getchar();
		while (c != '\n') {
			c = getchar();
		}
		//getchar();
		eingabeFixed(buff, w);
		return;
	}
	//Ist die Eingabe innerhalb der gewünschten größe
	buff[n] = ' ';
	n++;
	for (; n < w; n++) {
		buff[n] = ' ';
	}
	buff[n] = '|';
	buff[++n] = '\0';

	//test
}
