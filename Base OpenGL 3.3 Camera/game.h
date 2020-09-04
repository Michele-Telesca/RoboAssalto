#pragma once
#include "cube.h"
#include "gameMap.h"
#include "player.h";


/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {
public:

	game() {};

	gameMap gameMap;
	playerNostro p;

	void inizializza();
	void draw();

};

game gameuno;

void game::inizializza() {

	std::cout << "OK";

	p = playerNostro (1.0f,0.5f,0.0f);
	gameMap.initMap();

}

void game::draw() {

	gameMap.drawMap();
	p.draw();

}