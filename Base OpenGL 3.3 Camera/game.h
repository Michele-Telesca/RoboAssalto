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
	
	gameMap* mappa;						 //MAPPA
	player* p;							 //PLAYER
	vector <villain*> botList;			 //BOT
	int difficolta;                      //livello di difficoltà del gioco, che incrementa durante la partita (da 1 a 6)

	vector <villain*> modelBotList;    //lista dei bot
	vector <path*> pathList;		     //lista dei path

	glm::vec3 mousePoint;

	//costruttore
	game() {
		mappa = new gameMap();
		p = new player();
	};

	void inizializza();
	void initPathList();
	void initModelBotList();
	void draw(Shader lightShader, Shader animShader, glm::mat4 view);
	void add_BOT(int i);
	void kill_BOT();
	void spawn_BOT(path* path, int index);
	void BOT_spawner();

	glm::vec3 getMousePoint() {
		return mousePoint;
	}

	void setMousePoint(glm::vec3 w) {
		mousePoint = w;
	}

	// get //
	gameMap* getGameMap() {
		return mappa;
	}

	player* getPlayer() {
		return p;
	}

	vector <villain*> getBotList() {
		return botList;
	}


	// set //
	void setGameMap(gameMap* gamemap) {
		mappa = gamemap;
	}

	void getPlayer(player* player) {
		p = player;
	}

};

void game::initModelBotList() {
	//inizializzo 12 modelli di bot -> 4 per tipo
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);        //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_COP);			 //bot di tipo 3
	add_BOT(ZOMBIE_COP);			 //bot di tipo 3
	add_BOT(ZOMBIE_COP);			 //bot di tipo 3
	add_BOT(ZOMBIE_COP);			 //bot di tipo 3
}

void game::initPathList() {
	path* path1 = new path();
	path1->inizializzaPath(path1_Matrix);
	pathList.push_back(path1);

	path* path2 = new path();
	path2->inizializzaPath(path2_Matrix);
	pathList.push_back(path2);

	path* path3 = new path();
	path3->inizializzaPath(path3_Matrix);
	pathList.push_back(path3);

	path* path4 = new path();
	path4->inizializzaPath(path4_Matrix);
	pathList.push_back(path4);

	path* path5 = new path();
	path5->inizializzaPath(path5_Matrix);
	pathList.push_back(path5);

	path* path6 = new path();
	path6->inizializzaPath(path6_Matrix);
	pathList.push_back(path6);

	path* path7 = new path();
	path7->inizializzaPath(path7_Matrix);
	pathList.push_back(path7);

	path* path8 = new path();
	path8->inizializzaPath(path8_Matrix);
	pathList.push_back(path8);

	path* path9 = new path();
	path9->inizializzaPath(path9_Matrix);
	pathList.push_back(path9);

	path* path10 = new path();
	path10->inizializzaPath(path10_Matrix);
	pathList.push_back(path10);
}

void game::kill_BOT() {
	
	for (int i = 0; i < botList.size(); i++) {
		if (botList[i]->isDead == true) {
			botList.erase(botList.begin() + i); //elimina dall botList il bot in posizione i
		}
	}
	
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
	modelBotList.push_back(bot);
}

void game::BOT_spawner() { //N = numero di bot da spawnare
	if (botList.empty()) { //se la lista di bot NON è vuota
		cout << "*** Entrato nello spawner - botList.size: " << botList.size() << endl;

		if (difficolta <= 6) {
			difficolta++; //aumento la difficoltà
		}
		int N = difficolta;
		
		//inserisco N indici diversi (random) all'interno di una lista
		//ogni indice  sarà associato ad un bot della modelBotList
		vector <int> bot_index;
		int j = 0;
		while (j <= N) {
			int index = randMToN(0, 11);
			if(!numeroGiaPresente(index, bot_index)){
				bot_index.push_back(index);
				j++;
			}
		}

		//inserisco N indici diversi (random) all'interno di una lista
		//ogni indice sarà associato ad un path della pathList
		vector <int> matrix_index;
		int i = 0; 
		while (i <= N) {
			int index = randMToN(0, 9);
			if (!numeroGiaPresente(index, matrix_index)) {
				matrix_index.push_back(index);
				i++;
			}
		}	


		//spawn dei bot (associando il modello di bot della prima lista ad un path della seconda lista)
		for (int i = 0; i < N; i++) {
			spawn_BOT(pathList[matrix_index[i]], bot_index[i]);
		}

		cout << "*** " << N << " Bot spawnati - botList.size: " << botList.size() << endl;

	}
}

void game::spawn_BOT(path* path, int index) {
	villain* new_bot = modelBotList[index];	    //se 0 1 2 3 4 ...
	new_bot->initVillain(path);					//inizializzo il bot
	botList.push_back(new_bot);					//lo inserisco nella lista dei bot 
}

void game::inizializza() {

	//inizializza player
	p->initPlayer();
	cout << "*** Player: Loaded -> Initialized" << endl;

	//inizializza mappa
	mappa->initMap();
	cout << "*** Map: Loaded -> Initialized" << endl;

	//inizializzo tutti i modelli bot
	initModelBotList();
	cout << "*** Bot Models: Loaded" << endl;

	//inizializzo tutti i path
	initPathList();
	cout << "*** Paths: Loaded" << endl;

	//setto la difficolta a 0
	difficolta = 0;

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
	mappa->drawMap(lightShader);

}


