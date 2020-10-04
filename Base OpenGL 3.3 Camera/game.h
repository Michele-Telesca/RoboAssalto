#pragma once
#include "gameMap.h"
#include "player.h"
#include "shader_s.h"
#include "shader_m.h"
#include "villain.h"
#include "globalPathData.h"
#include "path.h"
#include <vector>


/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {

public:

	gameMap* map;						//MAPPA
	player* p;							//PLAYER
	vector <villain*> botList;			//BOT

	vector <villain*> botTypes_list;    //lista dei bot

	glm::vec3 mousePoint;

	//costruttore
	game() {
		map = new gameMap();
		p = new player();
	};

	void inizializza();
	void draw(Shader lightShader, Shader animShader, glm::mat4 view);
	void add_BOT(int i);
	void kill_BOT();
	void spawn_BOT(int path_Matrix[DIM][DIM], int index);

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

void game::kill_BOT() {
	botList.pop_back();
}

void game::add_BOT(int i) {
	villain* bot = new villain();
	if (i == ZOMBIE_PRISONER) {     //zombie difficoltà: 1
		bot->initModel_Zombie1();
	}
	else if (i == ZOMBIE_DERRICK) { //zombie difficoltà: 2
		bot->initModel_Zombie2();
	}
	else if (i == ZOMBIE_COP) {     //zombie difficoltà: 3
		bot->initModel_Zombie3();
	}
	botTypes_list.push_back(bot);
}

void game::spawn_BOT(int path_Matrix[DIM][DIM], int index) {
	villain* new_bot = botTypes_list[index];	//se 0 1 2 3 4 ...
	new_bot->initVillain(path_Matrix);			//inizializzo il bot
	botList.push_back(new_bot);					//lo inserisco nella lista dei bot 
}

void game::inizializza() {

	//inizializza player
	p->initPlayer();
	cout << "***player inizillzato" << endl;

	//inizializza mappa
	map->initMap();
	cout << "***mappa inizillzata" << endl;

	//inizializza le tipologie di bot
	add_BOT(ZOMBIE_PRISONER);		//bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		//bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);       //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		//bot di tipo 1
	add_BOT(ZOMBIE_DERRICK);		//bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		//bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		//bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		//bot di tipo 2
	add_BOT(ZOMBIE_COP);			//bot di tipo 3
	add_BOT(ZOMBIE_COP);			//bot di tipo 3
	add_BOT(ZOMBIE_COP);			//bot di tipo 3
	add_BOT(ZOMBIE_COP);			//bot di tipo 3
}

void game::draw(Shader lightShader, Shader animShader, glm::mat4 view) {

	//DRAW PLAYER
	p->drawPlayer(animShader, lightShader, view, getMousePoint());

	//DRAW BOTS
	if (botList.size() >= 1) {
		for (int i = 0; i < botList.size(); i++) {
			botList[i]->drawVillain(animShader, view);
		}
	}

	//DRAW MAP
	map->drawMap(lightShader);

}


