#pragma once
#include "gameMap.h"
#include "player.h";
#include "shader_s.h"
#include "shader_m.h"
#include "villain.h"
#include "globalPathData.h"
#include "path.h"
#include <vector>


/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {

private:

	gameMap* map;
	player* p;
	vector <villain*> botList;

	glm::vec3 mousePoint;

public:

	//costruttore
	game() {
		map = new gameMap();
		p = new player();
	};

	void inizializza();
	void draw(Shader lightShader);
	void spawn_BOT(int path_Matrix[DIM][DIM]);
	void moveAllBots();


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

	vector <villain*> getBotList() {
		return botList;
	}


	// set //
	void setGameMap(gameMap* gamemap) {
		map = gamemap;
	}

	void getPlayer(player* player) {
		p = player;
	}

};

void game::spawn_BOT(int path_Matrix[DIM][DIM]) {
	villain* bot = new villain();
	bot->initVillain(path_Matrix);
	botList.push_back(bot);
}

void game::inizializza() {

	//inizializza player
	p->initPlayer();

	//inizializza mappa
	map->initMap();
}

void game::draw(Shader lightShader) {

	//DRAW PLAYER
	p->drawPlayer(lightShader, getMousePoint()); 
	
	//DRAW MAP
	map->drawMap(lightShader);

	//DRAW BOTS
	if (botList.size() >= 1) {
		for (int i = 0; i < botList.size(); i++) {
			botList[i]->drawVillain(lightShader);
		}
	}

}

//void game::moveAllBots() {
//	if (botList.size() >= 1) {
//		for (int i = 0; i < botList.size(); i++) {
//			botList[i]->move(p->getX(), p->getZ());
//		}
//	}
//}

