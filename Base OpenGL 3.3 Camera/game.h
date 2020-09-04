#pragma once
#include "cube.h"
#include "gameMap.h"
#include "player.h";

/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {

private:

	gameMap* map;
	player* p;

public:

	//costruttore
	game() {
		map = new gameMap();
		p = new player();
	};

	void inizializza();
	void draw();

	// get //
	gameMap* getGameMap() {
		return map;
	}

	player* getPlayer() {
		return p;
	}
	
	// set //
	void setGameMap(gameMap* gamemap) {
		map = gamemap;
	}

	void getPlayer(player* player) {
		p = player;
	}

};

void game::inizializza() {

	p->initPlayer();
	map->initMap();

}

void game::draw() {

	p->drawPlayer();
	map->drawMap();

}