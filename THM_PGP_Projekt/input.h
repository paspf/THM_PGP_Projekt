#pragma once
#define BUFFERSIZE 255
#define _MAX_NAME_LENGTH 11


/*
	reads char from input to buffer
*/
void input(char *buff) {


	int i = 0;
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
reads fixed width string from input
*/
void inputFixed(char *buff, int w) {

	int count = 0;												// count of the entered chars
	do {

		buff[count] = getchar();

		if (buff[count] == '\n') {
			buff[count] = '\0';
			break;
		}
		count++;
	} while (count < BUFFERSIZE - 1 && count < w);
	//checks the count is greater than the given width w
	if (count >= w) {
		printf("ZU GROSS, NOCHMAL\n");
		char c = getchar();
		while (c != '\n') {
			c = getchar();
		}
		inputFixed(buff, w);
		return;
	}
	//If count is within the given width
	buff[count] = ' ';
	count++;
	for (; count < w; count++) {
		buff[count] = ' ';
	}
	buff[count] = '|';
	buff[++count] = '\0';
}
