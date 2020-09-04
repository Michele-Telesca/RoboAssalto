#pragma once
#include "cube.h"
#include "gameMap.h"
#include "player.h";

/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {
public:

	gameMap* map;
	player* p;

	//costruttore
	game() {
		map = new gameMap();
		p = new player();
	};

	void inizializza();
	void draw();

};

void game::inizializza() {

	p = new player(1.0f, 0.5f, 0.0f);
	map->initMap();

}

void game::draw() {

	map->drawMap();
	p->draw();

}