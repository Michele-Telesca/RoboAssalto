#pragma once
#include "cube.h"
#include "gameMap.h"


/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {
public:
	game() {};

	gameMap gameMap;

	void init();
	void draw();

};

void game::init() {

	gameMap.initMap();

}

void game::draw() {

	gameMap.drawMap();

}