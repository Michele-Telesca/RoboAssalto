#pragma once
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "game.h"

/* classe Update qui vengono gestiti tutti
gli aggiornamenti relativi allo stato degli 
oggetti in game*/

class update {
public:

	update();

};


void muoviDestra(game gameuno) {
	gameuno.p.x = gameuno.p.x + 7.3f;
	std::cout << "x: " << gameuno.p.x << "\n";
}

void muoviSinistra(game gameuno) {
	gameuno.p.x = gameuno.p.x  - 10.3f;
	std::cout << "x: " << gameuno.p.x << "\n";

}