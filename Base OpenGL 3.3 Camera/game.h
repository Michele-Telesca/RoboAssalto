#pragma once
#include "cube.h"
#include "gameMap.h"
#include "player.h";
#include "shader_s.h"
#include "shader_m.h"
#include "villain.h"
#include "globalPathData.h"
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
		//bot_path1 = new villain();
	};

	void inizializza();
	void draw(Shader lightShader);
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

	void spawn_botPath1() {
		villain* bot = new villain();
		bot->initVillain(path1_Matrix);
		botList.push_back(bot);
	}

	void spawn_botPath2() {
		villain* bot = new villain();
		bot->initVillain(path2_Matrix);
		botList.push_back(bot);
	}

	void spawn_botPath3() {
		villain* bot = new villain();
		bot->initVillain(path3_Matrix);
		botList.push_back(bot);
	}

};

void game::inizializza() {

	p->initPlayer();
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

void game::moveAllBots() {
	if (botList.size() >= 1) {
		for (int i = 0; i < botList.size(); i++) {
			botList[i]->move();
		}
	}

}

