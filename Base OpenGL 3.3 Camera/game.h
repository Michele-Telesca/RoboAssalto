#pragma once
#include "cube.h"
#include "gameMap.h"
#include "player.h";
#include "shader_s.h"
#include "shader_m.h"

/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {

private:

	gameMap* map;
	player* p;
	glm::vec3 mousePoint;

public:

	//costruttore
	game() {
		map = new gameMap();
		p = new player();
	};

	void inizializza();
	void draw(Shader lightShader);

	glm::vec3 getMousePoint() {
		return mousePoint;
	}

	void setMousePoint(glm::vec3 w) {
		mousePoint = w;
	}

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

void game::draw(Shader lightShader) {

	p->drawPlayer(lightShader, getMousePoint());
	map->drawMap(lightShader);

}