#pragma once
#include "eingabe.h"
#pragma warning (disable : 4996)
#define _MAX_NAME_LENGTH 11
#define _LIST_ENTRYS 10


//Spielereintrag mit Spielernamen und zugehörigen Punktestand
struct user {
	int score;
	char name[_MAX_NAME_LENGTH + 1];
};

//Liest die Punktestände in Reihenfolge in scores ein
void readScore(FILE* fp, int *scores) {

	char temp[BUFFERSIZE];

	int x = 0;


	while (!feof(fp) && x <_LIST_ENTRYS + 1) {
		char c = fgetc(fp);
		if (c == '|') {

			for (int i = 0; !feof(fp) && c != '\n'; i++) {

				c = fgetc(fp);
				temp[i] = c;

			}
			scores[x] = atoi(temp);
			x++;

		}
	}

}

//Liest Spielernamen in List ein
void readNames(FILE * fp, user  list[]) {

	//File Pointer auf anfang der Datei setzen
	fseek(fp, 0, SEEK_SET);

	char buff[BUFFERSIZE];
	char waste[BUFFERSIZE];

	char c;

	int secCounter = 0;
	//2 ersten Zeilen überspringen
	if (!feof(fp)) {
		fgets(waste, BUFFERSIZE, fp);
		fgets(waste, BUFFERSIZE, fp);
	}

	while (!feof(fp) && secCounter < _LIST_ENTRYS + 1) {


		for (int i = 0; !feof(fp) && i < _MAX_NAME_LENGTH + 1; i++) {
			c = fgetc(fp);
			if (isalnum(c) || c == ' ') buff[i] = c;
			// | als Trennzeichen Zwischen Namen und Spielstand
			if (c == '|' || secCounter >= _LIST_ENTRYS + 1) {
				//buff als Nullterminierter string( '|' wird überschrieben
				//buff[i] = '\0';
				std::copy(buff, buff + _MAX_NAME_LENGTH, list[secCounter].name);		// Kopiert Elemente im Bereich

				//list[secCounter].name[_MAX_NAME_LENGTH] = '\0';

				secCounter++;
				//Buff mit leer überschreiben
				for (int i = 0; i < _MAX_NAME_LENGTH; i++) {
					buff[i] = ' ';
				}
				c = fgetc(fp);
				break;
			}

		}
		//Bis zur nächsten zeile weiterlesen
		while (c != '\n' && !feof(fp)) {
			c = fgetc(fp);
		}

	}


}


void sortEntrys(user list[]) {
	//Bubblesort
	for (int i = _LIST_ENTRYS + 1; i > 1; i--) {
		for (int a = 0; a < i - 1; a++) {
			if (list[a].score < list[a + 1].score) {
				user temp = list[a];
				list[a] = list[a + 1];
				list[a + 1] = temp;
			}
		}
	}


}

//löscht alte score liste und erstellt neue auf basis der übergebenen Liste
void saveToFile(FILE* fp, user list[]) {
	fclose(fp);
	remove("scoreboard.txt");
	fp = fopen("scoreboard.txt", "w");

	fputs("#########\nName ", fp);
	for (int i = 0; i < _MAX_NAME_LENGTH - 4; i++) {
		fputc(' ', fp);
	}
	fputs("Score\n", fp);
	for (int i = 0; i < 10; i++) {
		if (list[i].name == '\0' || list[i].score < 0)break;
		char buff[BUFFERSIZE];
		fputs(list[i].name, fp);
		fputc('|', fp);
		itoa(list[i].score, buff, 10);
		fputs(buff, fp);
		fputc('\n', fp);
	}
	fclose(fp);

}

struct user* convertList()
{


	int scores[_LIST_ENTRYS + 1];

	user list[_LIST_ENTRYS + 1] = {};
	FILE *fPointer = fopen("scoreboard.txt", "r+");
	if (fPointer == 0) {
		printf("Datei ist nicht vorhanden oder konnte nicht geoeffnet werden!\n");
		return NULL;
	}
	readScore(fPointer, scores);

	readNames(fPointer, list);

	for (int i = 0; i < _LIST_ENTRYS + 1; i++) {
		list[i].score = scores[i];
	}

	//Sort Entrys
	sortEntrys(list);


	// Save to file
	saveToFile(fPointer, list);

	fclose(fPointer);

	return list;

}

void saveScoreToFile(int score)
{

	user* list;

	//Eingabe Ausgabe Buffer
	char singleLine[BUFFERSIZE];
	char e[BUFFERSIZE];


	//Öffne Datei
	FILE * fPointer;
	fPointer = fopen("scoreboard.txt", "r+");

	//Gibt es die Datei schon?!
	if (fPointer <= 0) {
		//wenn nicht Erstell neue Datei mit dem Namen und Format 
		// TODO:! Formatierung
		fPointer = fopen("scoreboard.txt", "w+");
		fputs("#########\nName ", fPointer);
		for (int i = 0; i < _MAX_NAME_LENGTH - 4; i++) {
			fputc(' ', fPointer);
		}
		fputs("Score \n", fPointer);
		printf("Score  %i\n", score);
		printf("Gib deine Namen ein(max 10 Zeichen): ");

		//Spielername mit gesetzter Weite
		eingabeFixed(e, _MAX_NAME_LENGTH);



		printf("\n");
		//Speichern des Namens in Datei
		fputs(e, fPointer);
		//Speichern des Scores
		itoa(score, e, 10);
		fputs(e, fPointer);
		system("cls");

	}
	else {
		printf("Score  %i\n", score);
		printf("Gib deine Namen ein(max 10 Zeichen): ");

		fseek(fPointer, 0, SEEK_END);
		//fputc('\n', fPointer);
		//Spielername mit gesetzter Weite
		eingabeFixed(e, _MAX_NAME_LENGTH);

		printf("\n");
		//Speichern des Namens in Datei
		fputs(e, fPointer);
		//Speichern des Scores
		itoa(score, e, 10);
		fputs(e, fPointer);
		system("cls");


	}
	rewind(fPointer);

	//Ausgabe der Scoreliste
	while (!feof(fPointer)) {

		fgets(singleLine, BUFFERSIZE, fPointer);

		printf(singleLine);
	}

	fclose(fPointer);
	//getchar();

}

void showScorelist() {
	FILE * fp = fopen("scoreboard.txt", "r");
	if (fp <= 0) {
		puts("Scoreliste nicht gefunden!");
		return;
	}
	while (!feof(fp)) {
		char c = fgetc(fp);
		putchar(c);
	}
	fclose(fp);

}




