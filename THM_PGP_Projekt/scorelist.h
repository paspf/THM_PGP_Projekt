#pragma once
#include "input.h"
#pragma warning (disable : 4996)
#define _MAX_NAME_LENGTH 11
#define _LIST_ENTRYS 10

//user entry with name and score
struct user {
	int score;
	char name[_MAX_NAME_LENGTH + 1];
};

//reads scores in decreasing order
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

//reads playernames into list
void readNames(FILE * fp, user  list[]) {

	//seek filepointer to the beginning
	fseek(fp, 0, SEEK_SET);

	char buff[BUFFERSIZE];
	char waste[BUFFERSIZE];

	char c;

	int secCounter = 0;
	//ignore first 2 rows
	if (!feof(fp)) {
		fgets(waste, BUFFERSIZE, fp);
		fgets(waste, BUFFERSIZE, fp);
	}

	while (!feof(fp) && secCounter < _LIST_ENTRYS + 1) {


		for (int i = 0; !feof(fp) && i < _MAX_NAME_LENGTH + 1; i++) {
			c = fgetc(fp);
			if (isalnum(c) || c == ' ') buff[i] = c;
			// | as seperator between name and scores
			if (c == '|' || secCounter >= _LIST_ENTRYS + 1) {
				std::copy(buff, buff + _MAX_NAME_LENGTH, list[secCounter].name);		// Kopiert Elemente im Bereich


				secCounter++;
				//overwrite buff with empty space
				for (int i = 0; i < _MAX_NAME_LENGTH; i++) {
					buff[i] = ' ';
				}
				c = fgetc(fp);
				break;
			}

		}
		//read until next line
		while (c != '\n' && !feof(fp)) {
			c = fgetc(fp);
		}

	}


}


inline void sortEntrys(user list[]) {
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

//deletes old scorelist and creates a new one on he basis of the new list
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

	//input output buffer
	char singleLine[BUFFERSIZE];
	char e[BUFFERSIZE];


	FILE * fPointer;
	fPointer = fopen("scoreboard.txt", "r+");

	if (fPointer <= 0) {
		//if file doesnt exist create new
		fPointer = fopen("scoreboard.txt", "w+");
		fputs("#########\nName ", fPointer);
		for (int i = 0; i < _MAX_NAME_LENGTH - 4; i++) {
			fputc(' ', fPointer);
		}
		fputs("Score \n", fPointer);
		printf("\nScore  %i\n", score);
		printf("Gib deine Namen ein(max 10 Zeichen): ");

		//player name
		inputFixed(e, _MAX_NAME_LENGTH);



		printf("\n");
		//save name to file
		fputs(e, fPointer);
		//save score
		itoa(score, e, 10);
		fputs(e, fPointer);
		fputs("\n", fPointer);
		system("cls");

	}
	else {
		printf("\nScore  %i\n", score);
		printf("Gib deine Namen ein(max 10 Zeichen): ");

		fseek(fPointer, 0, SEEK_END);
		//player name
		inputFixed(e, _MAX_NAME_LENGTH);

		printf("\n");
		//save name
		fputs(e, fPointer);
		//save score
		itoa(score, e, 10);
		fputs(e, fPointer);
		fputs("\n", fPointer);
		system("cls");


	}
	rewind(fPointer);

	//ouput scorelist to screen
	while (!feof(fPointer)) {

		fgets(singleLine, BUFFERSIZE, fPointer);

		printf(singleLine);
	}

	fclose(fPointer);
	convertList();
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




