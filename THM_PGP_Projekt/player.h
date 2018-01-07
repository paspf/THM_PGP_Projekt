#pragma once
#include <stdio.h>
#include "graphics.h"

#define PLAYER_X 3
#define PLAYER_GRAV .2f

struct player {
	float y; 
	float dy;
	bool jump;
}player;

void initPlayer() {
	player.y = HEIGHT-1;
	player.dy = PLAYER_GRAV;
	player.jump = false;

}

void jump() {
	player.dy = -2;
	player.jump = true;
}
//draws player to screen
void drawPlayer() {
	putPixel(PLAYER_X, player.y, ' ', BACKGROUND_BLUE);
}

void updatePlayer(float time) {
//check keyboard input
	if (kbhit()) {
		char c = getch();
//if spacebar is pressed and player is not already jumping
		if (c == ' '&&!player.jump)jump();
	}
//update player position
	player.y += player.dy * time;				//s(t) = v * t
	player.dy += PLAYER_GRAV * time;			//a(t) = g * t
	if (player.y >= HEIGHT - 1){
		player.y = HEIGHT - 1;
		player.jump = false;
	}
}
//checks if player collided with an obstackle
bool checkDead() {
	return screen[(int)(PLAYER_X + player.y * WIDTH)].Attributes == BACKGROUND_RED;
}

