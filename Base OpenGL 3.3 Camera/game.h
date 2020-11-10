#pragma once
#include "gameMap.h"
#include "player.h"
#include "shader_s.h"
#include "shader_m.h"
#include "villain.h"
#include "globalPathData.h"
#include "path.h"
#include "powerUp.h"
#include "loading.h"

#include <vector>

/*classe game qui vengono gestiti tutte le azioni relative
alla partita e inizializzati tutti gli oggetti*/
class game {

public:
	
	//Da renderizzare:
	gameMap* mappa;						 //MAPPA
	player* p;							 //PLAYER
	vector <villain*> spawnedBotList;	 //LISTA DEI BOT SPAWNATI
	powerUp* power_up;					 //POWER UP

	vector <villain*> modelBotList;      //Lista dei modelli di bot
	vector <path*> pathList;		     //Lista dei path

	int difficolta;                      //Livello di difficoltà del gioco, che incrementa durante la partita (da 1 a 6)

	bool gameInitialized;
	bool inGame;
	bool gamePause;

	loading* loadingGame;

	glm::vec3 mousePoint;				 //Coordinate del mouse

	unsigned int textureLifeBar;
	unsigned int textureShadow;

	bool startGameSoundtrack;

	//Costruttore
	game() {
		mappa = new gameMap();
		p = new player();
		power_up = new powerUp();
		loadingGame = new loading();
		startGameSoundtrack = false;
	};

	// -- Prototipi -- //
	void init(int selectedPlayer, int weaponType); //inizializza il game game
	void initPathList(); //inizializza tutti i path dei bot
	void initModelBotList(); //inizializza la modelBotList (caricamento di tutti i bot spawnabili nel gioco)
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
	//inizializzo i di bot

	if (loadingGame->statusLoading == 50) {
		villain* zombie1 = new villain();
		zombie1->initModel_Zombie1();
		modelBotList.push_back(zombie1);
	}

	if (loadingGame->statusLoading == 60) {
		villain* zombie2 = new villain();
		zombie2->initModel_Zombie2();
		modelBotList.push_back(zombie2);
	}

	if (loadingGame->statusLoading == 80) {
		villain* zombie3 = new villain();
		zombie3->initModel_Zombie3();
		modelBotList.push_back(zombie3);
	}
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


void game::BOT_spawner() { //N = numero di bot da spawnare
	if (spawnedBotList.empty()) { //se la lista di bot NON è vuota

		if (difficolta <= 6) {
			difficolta++; //aumento la difficoltà
		}
		int N = difficolta;
		
		//inserisco N indici random all'interno di una lista
		//ogni indice sarà associato ad un tipo di bot della modelBotList
		vector <int> bot_index;
		for (int i = 0; i < difficolta; i++) {
			int index = randMtoN(0, modelBotList.size());
			bot_index.push_back(index);
		}

		//inserisco N indici diversi (random) all'interno di una lista
		//ogni indice sarà associato ad un path della pathList
		vector <int> matrix_index;
		int i = 0; 
		while (i <= N) {
			int index = randMtoN(0, pathList.size());
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

	villain* new_zombie = new villain();
	new_zombie->botType = modelBotList[index]->botType;
	new_zombie->meshAttacking = modelBotList[index]->meshAttacking;
	new_zombie->meshHit = modelBotList[index]->meshHit;
	new_zombie->meshDead = modelBotList[index]->meshDead;
	new_zombie->meshWalking = modelBotList[index]->meshWalking;
	new_zombie->textureShadow = textureShadow;
	new_zombie->initVillain(path);
	new_zombie->textureLifeVillain = textureLifeBar;
	spawnedBotList.push_back(new_zombie); //lo inserisco nella lista dei bot
}

void game::powerUp_spawner() {
	if (power_up->spawned == false) {
		cout << "1 spawner: " << endl;
		power_up->spawned = true;

		int list_powerUp_index = randMtoN(0, power_up->spawnCoordsList.size()-1);
		glm::vec3 powerUp_coord = power_up->spawnCoordsList[list_powerUp_index];
		power_up->x = powerUp_coord.x;
		power_up->y = powerUp_coord.y;
		power_up->z = powerUp_coord.z;

		int i = randMtoN(1, 2);
		if (p->life <= PLAYER_LIFE/4 || p->chest_life <= CHEST_LIFE/4) {
			power_up->powerUp_type = MEDIKIT;
		}
		else {
			//Se il player possiede lo shotgun -> il powerUp che spawnerà sarà lo sniper
			if (p->wea->weapon_type == WEAPON_SHOTGUN) {
				power_up->powerUp_type = WEAPON_SNIPER;
			}
			//Se il player possiede lo sniper -> il powerUp che spawnerà sarà lo shotgun
			else if (p->wea->weapon_type == WEAPON_SNIPER) {
				cout << "2 setto il powerup type " << endl;
				power_up->powerUp_type = WEAPON_SHOTGUN;
			}
		}

	}
}

void game::init(int selectedPlayer, int weaponType) {

	//Se il game non è stato ancora inizializzato
	if (gameInitialized == false) {

		if (loadingGame->statusLoading == 0.0f) {
			// init MAP
			mappa->initMap();
			cout << "*** Map: Loaded -> Initialized" << endl;
		}

		if (loadingGame->statusLoading == 15.0f) {
			// init PLAYER
			p->initPlayer(selectedPlayer, weaponType);
			cout << "*** Players: Loaded -> Initialized" << endl;
		}

		if (loadingGame->statusLoading >= 50 && loadingGame->statusLoading < 90) {
			// init BOT models
			initModelBotList();
			cout << "*** Bot Models: Loaded" << endl;
		}

		if (loadingGame->statusLoading == 90.0f) {
			// init PATH
			initPathList();
			cout << "*** Paths: Loaded" << endl;

			// init POWERUP
			power_up->initPowerUp();
			cout << "*** PowerUp: Loaded" << endl;

			difficolta = 0;
			cout << "*** Difficolta: 0" << endl;

			

			gameInitialized = true;	//segnalo che l'init del game è stato completato completato
			cout << "*** INIT GAME: COMPLETED" << endl;
		}
	}

	//Se il game è già stato inizializzato. Resetto animazioni e posizioni del player e dei bot
	else if (gameInitialized == true) {

		if (loadingGame->statusLoading == 1.0f) {

			//Elimino tutti i bot spawnati
			for (int i = 0; i < spawnedBotList.size(); i++) {
				spawnedBotList.pop_back();
			}
			
			//resetto il player
			p->resetPlayer(selectedPlayer, weaponType);

			//resetto il powerUp
			power_up->spawned = false;

			//resetto la difficoltà a 0
			difficolta = 0;

		}
	}

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
	simpleShader.setVec4("color", 1.0f, 1.0f, 1.0f, 1.0f);

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
	lightShader.setVec3("colormodel", 1.0f, 1.0f, 1.0f);

}

void game::draw(Shader simpleShader, Shader lightShader, Shader animShader, glm::mat4 view) {
	
	//Setto le proprietà view, projection degli shaders
	setShadersProperties(simpleShader, lightShader, animShader, view); 

	//DRAW MAP
	mappa->drawMap(simpleShader, lightShader, view);

	//DRAW PLAYER

	//DRAW BOTS
	if (spawnedBotList.size() >= 1) {
		for (int i = 0; i < spawnedBotList.size(); i++) {

			
			spawnedBotList[i]->drawVillain(animShader,simpleShader);
			
		}
	}
	
	

	//DRAW PLAYER
	p->drawPlayer(simpleShader, animShader, getMousePoint());

	//DRAW POWERUP
	if (power_up->spawned) {
		power_up->drawPowerUp(lightShader);
	}

}


