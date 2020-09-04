#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "game.h"
#include "gameMap.h"
#include "player.h"


/* classe Update qui vengono gestiti tutti
gli aggiornamenti relativi allo stato degli 
oggetti in game*/

class update {
public:

	update();

};

void moveDx(game* gameuno) {
	gameuno->p->x = gameuno->p->x + 0.3f;
}

void moveSx(game* gameuno) {
	gameuno->p->x = gameuno->p->x  - 0.3f;
}

void moveUp(game* gameuno) {
	gameuno->p->z = gameuno->p->z - 0.3f;
}

void moveDown(game* gameuno) {
	gameuno->p->z = gameuno->p->z + 0.3f;
}
