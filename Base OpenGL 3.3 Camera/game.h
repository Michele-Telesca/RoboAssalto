#pragma once
#include "gameMap.h"
#include "player.h"
#include "shader_s.h"
#include "shader_m.h"
#include "villain.h"
#include "globalPathData.h"
#include "path.h"
#include "powerUp.h"
#include <vector>

/*classe game qui vengono gestiti tutte le azioni relatie
alla partita e inizializzati tutti gli oggetti*/
class game {

public:
	
	//Da renderizzare:
	gameMap* mappa;						 //MAPPA
	player* p;							 //PLAYER
	vector <villain*> spawnedBotList;	 //LISTA DEI BOT SPAWNATI
	powerUp* power_up;					 //POWER UP

	vector <villain*> modelBotList;      //Lista dei bot caricati nel gioco
	vector <path*> pathList;		     //Lista dei path

	int difficolta;                      //Livello di difficoltà del gioco, che incrementa durante la partita (da 1 a 6)
	
	glm::vec3 mousePoint;				 //Coordinate del mouse

	//Costruttore
	game() {
		mappa = new gameMap();
		p = new player();
		power_up = new powerUp();
	};

	// -- Prototipi -- //
	void init(); //inizializza il game game
	void initPathList(); //inizializza tutti i path dei bot
	void initModelBotList(); //inizializza la modelBotList (caricamento di tutti i bot spawnabili nel gioco)
	void add_BOT(int i); //aggiunge un bot alla modelBotList 
	void setShadersProperties(Shader simpleShader, Shader lightShader, Shader animShader, glm::mat4 view); //setta le proprietà degli shader
	void draw(Shader simpleShader, Shader lightShader, Shader animShader, glm::mat4 view);

	void spawn_BOT(path* path, int index); //spawna un bot (lo inserisce nella botList)
	void kill_BOT(); //killa un bot
	void BOT_spawner(); //gestisce lo spawn dei bot
	void powerUp_spawner(); //gestisce lo spawn di powerUp

	// -- GET -- //
	gameMap* getGameMap() {
		return mappa;
	}

	player* getPlayer() {
		return p;
	}

	vector <villain*> getSpawnedBotList() {
		return spawnedBotList;
	}

	glm::vec3 getMousePoint() {
		return mousePoint;
	}

	// -- SET -- //
	void setGameMap(gameMap* gamemap) {
		mappa = gamemap;
	}

	void getPlayer(player* player) {
		p = player;
	}

	void setMousePoint(glm::vec3 w) {
		mousePoint = w;
	}

};

void game::initModelBotList() {
	//inizializzo 12 modelli di bot -> 4 per tipo
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);        //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_PRISONER);		 //bot di tipo 1
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
	add_BOT(ZOMBIE_DERRICK);		 //bot di tipo 2
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
	
	for (int i = 0; i < spawnedBotList.size(); i++) {
		if (spawnedBotList[i]->isDead == true) {
			spawnedBotList.erase(spawnedBotList.begin() + i); //elimina dall botList il bot in posizione i
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
	if (spawnedBotList.empty()) { //se la lista di bot NON è vuota

		if (difficolta <= 6) {
			difficolta++; //aumento la difficoltà
		}
		int N = difficolta;
		
		//inserisco N indici diversi (random) all'interno di una lista
		//ogni indice  sarà associato ad un bot della modelBotList
		vector <int> bot_index;
		int j = 0;
		while (j <= N) {
			int index = randMtoN(0, modelBotList.size()-1);
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
			int index = randMtoN(0, pathList.size()-1);
			if (!numeroGiaPresente(index, matrix_index)) {
				matrix_index.push_back(index);
				i++;
			}
		}	


		//spawn dei bot (associando il modello di bot della prima lista ad un path della seconda lista)
		for (int i = 0; i < N; i++) {
			spawn_BOT(pathList[matrix_index[i]], bot_index[i]);
		}

		cout << "--------> " << N << " Bot spawnati - botList.size(): " << spawnedBotList.size() << endl;

	}
}

void game::spawn_BOT(path* path, int index) {
	villain* new_bot = modelBotList[index];	    //se 0 1 2 3 4 ...
	new_bot->initVillain(path);					//inizializzo il bot
	spawnedBotList.push_back(new_bot);					//lo inserisco nella lista dei bot 
}

void game::powerUp_spawner() {
	if (power_up->spawned == false) {
		power_up->spawned = true;

		int list_powerUp_index = randMtoN(0, power_up->spawnCoordsList.size()-1);
		glm::vec3 powerUp_coord = power_up->spawnCoordsList[list_powerUp_index];
		power_up->x = powerUp_coord.x;
		power_up->y = powerUp_coord.y;
		power_up->z = powerUp_coord.z;

		int powerUp_index = randMtoN(1, 2);
		if (powerUp_index == POWERUP_BULLET) {
			power_up->powerUp_type = POWERUP_BULLET;
		}
		else if (powerUp_index == POWERUP_SIGHT) {
			power_up->powerUp_type = POWERUP_SIGHT;
		}
	}
}

void game::init() {

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

	//inizializzo i powerUp
	power_up->initPowerUp();
	cout << "*** PowerUp: Loaded" << endl;

	//setto la difficolta a 0
	difficolta = 0;
	cout << "*** Difficolta: 0" << endl;

}

void game::setShadersProperties(Shader simpleShader, Shader lightShader, Shader animShader, glm::mat4 view) {
	
	// ---- ANIMATION Shader ---- //
	animShader.use();

	//projection
	glm::mat4 projection_animation = glm::mat4(1.0f);	//identity matrix
	projection_animation = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	animShader.setMat4("projection", projection_animation);

	//view
	animShader.setMat4("view", view);

	//light properties
	animShader.setVec3("light.position", lightPos);
	animShader.setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
	animShader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);


	// ---- SIMPLE Shader ---- //
	simpleShader.use();

	//view
	simpleShader.setMat4("view", view);

	//projection
	glm::mat4 projection2 = glm::mat4(1.0f);	//identity matrix
	projection2 = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	simpleShader.setMat4("projection", projection2);

	// ---- LIGHT Shader ---- //
	lightShader.use();

	//projection
	glm::mat4 projection3 = glm::mat4(1.0f);	//identity matrix
	projection3 = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	lightShader.setMat4("projection", projection3);

	//view
	lightShader.setMat4("view", view);

	//light per la mappa
	lightShader.setVec3("light.position", lightPos);
	lightShader.setVec3("light.ambient", 0.5f, 0.5f, 0.5f);
	lightShader.setVec3("light.diffuse", 0.7f, 0.7f, 0.7f);
	lightShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
}

void game::draw(Shader simpleShader, Shader lightShader, Shader animShader, glm::mat4 view) {
	
	//Setto le proprietà view, projection degli shaders
	setShadersProperties(simpleShader, lightShader, animShader, view); 

	//DRAW PLAYER
	p->drawPlayer(simpleShader, animShader, getMousePoint());

	//DRAW BOTS
	if (spawnedBotList.size() >= 1) {
		for (int i = 0; i < spawnedBotList.size(); i++) {
			spawnedBotList[i]->drawVillain(animShader);
		}
	}
	
	//DRAW MAP
	mappa->drawMap(lightShader, view);

	//DRAW POWERUP
	if (power_up->spawned) {
		power_up->drawPowerUp(lightShader);
	}

}


